#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <stdexcept>

struct Rect {
    int topLeftX;
    int topLeftY;
    int bottomRightX;
    int bottomRightY;

    Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
        : topLeftX(x1), topLeftY(y1), bottomRightX(x2), bottomRightY(y2) {
    }
};

class ScreenCapture {
public:
    ScreenCapture() {
        // Get the screen dimensions
        DEVMODE dm;
        ZeroMemory(&dm, sizeof(dm));
        dm.dmSize = sizeof(dm);
        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
            screenShotArea.topLeftX = 0;
            screenShotArea.topLeftY = 0;
            screenShotArea.bottomRightX = dm.dmPelsWidth;
            screenShotArea.bottomRightY = dm.dmPelsHeight;
        }
        else {
            // Error: couldn't get resolution.
        }
        hScreenDC = GetDC(NULL);
        hMemoryDC = CreateCompatibleDC(hScreenDC);
    }

    ScreenCapture(Rect ssa) {
        // Get the screen dimensions
        DEVMODE dm;
        ZeroMemory(&dm, sizeof(dm));
        dm.dmSize = sizeof(dm);
        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
            int screenWidth = dm.dmPelsWidth;
            int screenHeight = dm.dmPelsHeight;

            // Map the points to the active screen resolution
            screenShotArea.topLeftX = (int)((double)ssa.topLeftX * screenWidth / dm.dmPelsWidth);
            screenShotArea.topLeftY = (int)((double)ssa.topLeftY * screenHeight / dm.dmPelsHeight);
            screenShotArea.bottomRightX = (int)((double)ssa.bottomRightX * screenWidth / dm.dmPelsWidth);
            screenShotArea.bottomRightY = (int)((double)ssa.bottomRightY * screenHeight / dm.dmPelsHeight);
        }
        else {
            // Error: couldn't get resolution.
        }
        hScreenDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
        hMemoryDC = CreateCompatibleDC(hScreenDC);
    }

    ~ScreenCapture() {
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
    }

    Rect getRect() const {
        return screenShotArea;
    }

    cv::Mat capture() {
        int rect_width = screenShotArea.bottomRightX - screenShotArea.topLeftX;
        int rect_height = screenShotArea.bottomRightY - screenShotArea.topLeftY;
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, rect_width, rect_height);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

        BitBlt(hMemoryDC, 0, 0, rect_width, rect_height, hScreenDC, screenShotArea.topLeftX,
            screenShotArea.topLeftY, SRCCOPY);
        hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

        cv::Mat mat = HBitmapToMat(hBitmap);
        cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);

        DeleteObject(hBitmap);
        SelectObject(hMemoryDC, hOldBitmap);

        return mat;
    }

    cv::Point getCenter() const {
        return cv::Point((screenShotArea.topLeftX + screenShotArea.bottomRightX) / 2,
            (screenShotArea.topLeftY + screenShotArea.bottomRightY) / 2);
    }

    void show() {
        cv::Mat frame = capture();

        // Create a window to display the frame
        cv::namedWindow("Frame", cv::WINDOW_NORMAL);

        // Resize the window to match the frame size
        cv::resizeWindow("Frame", frame.cols, frame.rows);

        // Move the window to the top-left corner
        cv::moveWindow("Frame", 0, 0);

        // Show the frame in the window
        cv::imshow("Frame", frame);

        // Wait for a key press or window closure
        while (true) {
            int key = cv::waitKey(1);
            if (key >= 0)
                break;

            // Check if the window is still open
            if (cv::getWindowProperty("Frame", cv::WND_PROP_AUTOSIZE) < 0)
                break;
        }

        // Destroy the window
        cv::destroyWindow("Frame");
    }

private:
    cv::Mat HBitmapToMat(HBITMAP hBitmap) {
        BITMAP bmp;
        GetObject(hBitmap, sizeof(BITMAP), &bmp);

        BITMAPINFOHEADER bi;
        bi.biSize = sizeof(BITMAPINFOHEADER);
        bi.biWidth = bmp.bmWidth;
        bi.biHeight = -bmp.bmHeight;  //This is the line that makes it draw upside down or not.
        bi.biPlanes = 1;
        bi.biBitCount = 32;
        bi.biCompression = BI_RGB;
        bi.biSizeImage = 0;
        bi.biXPelsPerMeter = 0;
        bi.biYPelsPerMeter = 0;
        bi.biClrUsed = 0;
        bi.biClrImportant = 0;

        cv::Mat mat(cv::Size(bmp.bmWidth, bmp.bmHeight), CV_8UC4);
        SelectObject(hMemoryDC, hBitmap);
        GetDIBits(hMemoryDC, hBitmap, 0, bmp.bmHeight, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

        return mat;
    }
private:
    HDC hScreenDC;
    HDC hMemoryDC;
    Rect screenShotArea;
};

class Matcher {
public:
    Matcher(const std::string& filename, int matchMethod, double tolerance, Rect screenShotArea = Rect(), int matches = 1)
        : matchMethod(matchMethod), tolerance(tolerance), consecutiveMatches(1), MAX_MATCHES(matches),
        screenCapture(createScreenCapture(screenShotArea)) {
        templateImage = cv::imread(filename, cv::IMREAD_COLOR);

        if (templateImage.empty()) {
            std::string errorMessage = "Failed to load the template image.";
            std::cout << errorMessage << std::endl; // Log the error to the console
            throw std::runtime_error(errorMessage); // Throw an exception
        }
    }

    Matcher(const std::string& filename, double tolerance, Rect sreenShotArea = Rect(), int matches = 1)
        : Matcher(filename, cv::TM_CCOEFF_NORMED, tolerance, sreenShotArea, matches) {
    }

    Matcher(const std::string& filename, double tolerance, int matches)
        : Matcher(filename, cv::TM_CCOEFF_NORMED, tolerance, Rect(), matches) {
    }

    Matcher(const std::string& filename, int matchMethod, double tolerance, int matches = 1)
        : Matcher(filename, matchMethod, tolerance, Rect(), matches) {
    }

    bool templateMatch() {
        cv::Mat frame = screenCapture.capture();

        // Perform template matching
        cv::Mat result;
        cv::matchTemplate(frame, templateImage, result, matchMethod);

        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        cv::Point matchLoc;
        if (matchMethod == cv::TM_SQDIFF || matchMethod == cv::TM_SQDIFF_NORMED) {
            matchLoc = minLoc;
        }
        else {
            matchLoc = maxLoc;
        }

        // Check if the match is within the defined tolerance
        if (maxVal < tolerance) {
            consecutiveMatches = 1;
            return false; // Return invalid point if no match is found
        }
        else if (maxVal > tolerance && consecutiveMatches < MAX_MATCHES) {
            consecutiveMatches++;
            return false;
        }
        else {
            consecutiveMatches = 1;
            // Calculate the center of the matched region
            return true;
        }
    }

    bool templateMatch(cv::Point& center) {
        cv::Mat frame = screenCapture.capture();

        // Perform template matching
        cv::Mat result;
        cv::matchTemplate(frame, templateImage, result, matchMethod);

        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        cv::Point matchLoc;
        if (matchMethod == cv::TM_SQDIFF || matchMethod == cv::TM_SQDIFF_NORMED) {
            matchLoc = minLoc;
        }
        else {
            matchLoc = maxLoc;
        }

        // Check if the match is within the defined tolerance
        if (maxVal < tolerance) {
            consecutiveMatches = 0;
            center = cv::Point(-1, -1);
            return false; // Return invalid point if no match is found
        }
        else if (maxVal > tolerance && consecutiveMatches <= MAX_MATCHES) {
            consecutiveMatches++;
            center = cv::Point(-1, -1);
            return false;
        }
        else {
            consecutiveMatches = 0;
            // Calculate the center of the matched region
            center = cv::Point(matchLoc.x + templateImage.cols / 2, matchLoc.y + templateImage.rows / 2);
            center.x += screenCapture.getRect().topLeftX;
            center.y += screenCapture.getRect().topLeftY;
            return true;
        }
    }

#ifdef _DEBUG
    bool checkTolerance() {
        cv::Mat frame = screenCapture.capture();

        // Perform template matching
        cv::Mat result;
        cv::matchTemplate(frame, templateImage, result, matchMethod);

        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        cv::Point matchLoc;
        if (matchMethod == cv::TM_SQDIFF || matchMethod == cv::TM_SQDIFF_NORMED) {
            matchLoc = minLoc;
        }
        else {
            matchLoc = maxLoc;
        }

        std::cout << maxVal << ", " << tolerance << std::endl;
        // Check if the match is within the defined tolerance
        if (maxVal < tolerance) {
            consecutiveMatches = 1;
            return false; // Return invalid point if no match is found
        }
        else if (maxVal > tolerance && consecutiveMatches < MAX_MATCHES) {
            consecutiveMatches++;
            return false;
        }
        else {
            consecutiveMatches = 1;
            // Calculate the center of the matched region
            return true;
        }
    }
#endif
private:
    static ScreenCapture createScreenCapture(Rect ssa) {
        if (ssa.topLeftX == 0 && ssa.topLeftY == 0 && ssa.bottomRightX == 0 && ssa.bottomRightY == 0) {
            return ScreenCapture();
        }
        else {
            return ScreenCapture(ssa);
        }
    }
private:
    cv::Mat templateImage;
    int matchMethod;
    double tolerance;
    ScreenCapture screenCapture;
    int consecutiveMatches;
    const int MAX_MATCHES;
};

class EscapeKeyChecker {
public:
    EscapeKeyChecker(std::atomic<bool>& escapePressedRef) : escapePressed(escapePressedRef) {}

    void startChecking()
    {
        escapeThread = std::thread(&EscapeKeyChecker::checkEscapePressed, this);
    }

    void stopChecking()
    {
        escapePressed.store(false);
        if (escapeThread.joinable())
            escapeThread.join();
    }

private:
    std::atomic<bool>& escapePressed;
    std::thread escapeThread;

    void checkEscapePressed()
    {
        while (true)
        {
            // Check if escape key has been pressed
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                escapePressed.store(false);
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    }
};

void ClickScreen(int x, int y)
{
    // Set the mouse position
    SetCursorPos(x, y);

    // Simulate a left mouse button down event
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    // Simulate a left mouse button up event
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

int main() {
    std::atomic<bool> run(true);
    EscapeKeyChecker checker(run);
    checker.startChecking();

    Matcher target("images/target.png", 0.70, Rect(391, 244, 1006, 678));

    std::chrono::steady_clock::time_point lastClickTime = std::chrono::steady_clock::now();

    cv::Point targetCenter;
    while (run.load()) {
        if (target.templateMatch(targetCenter)) {
            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::milliseconds timeSinceLastClick = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastClickTime);
            std::cout << "Time between clicks: " << timeSinceLastClick.count() << " ms" << std::endl;

            ClickScreen(targetCenter.x, targetCenter.y);

            lastClickTime = currentTime;            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    checker.stopChecking();

    return 0;
}