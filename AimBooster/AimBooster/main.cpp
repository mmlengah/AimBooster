#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <memory>

struct Rect {
    int topLeftX;
    int topLeftY;
    int bottomRightX;
    int bottomRightY;

    Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
        : topLeftX(x1), topLeftY(y1), bottomRightX(x2), bottomRightY(y2) {
    }
};

class ScreenShot {
public:
    ScreenShot(const Rect& rect = Rect())
        : rect((rect.bottomRightX == 0 && rect.bottomRightY == 0) ?
            Rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)) : rect) {
    }

    cv::Mat screenshotColour() {
        capture();
        cv::Mat img3;
        cv::cvtColor(img, img3, cv::COLOR_BGRA2BGR);
        return img3;
    }

    cv::Mat screenshotGreyScale() {
        capture();
        cv::Mat grey;
        cv::cvtColor(img, grey, cv::COLOR_BGR2GRAY);
        return grey;
    }

    void display(bool grayscale = false) {
        cv::Mat dispImg = grayscale ? screenshotGreyScale() : screenshotColour();
        const std::string windowName = "Display window";

        // Create a window for display.
        cv::namedWindow(windowName, cv::WINDOW_NORMAL);

        // Set the window size to 600 x 400.
        cv::resizeWindow(windowName, 600, 400);

        // Move the window to the top left of the screen.
        cv::moveWindow(windowName, 0, 0);

        // Show our image inside the window.
        cv::imshow(windowName, dispImg);

        // Wait for a keystroke in the window
        cv::waitKey(0);
    }

    Rect getRect() const {
        return rect;
    }
private:
    void capture() {
        HDC hScreen = GetDC(NULL);
        HDC hDC = CreateCompatibleDC(hScreen);
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, rect.bottomRightX - rect.topLeftX, rect.bottomRightY - rect.topLeftY);
        SelectObject(hDC, hBitmap);
        BitBlt(hDC, 0, 0, rect.bottomRightX - rect.topLeftX, rect.bottomRightY - rect.topLeftY, hScreen, rect.topLeftX, rect.topLeftY, SRCCOPY);
        BITMAPINFOHEADER bmi = { 0 };
        bmi.biSize = sizeof(BITMAPINFOHEADER);
        bmi.biPlanes = 1;
        bmi.biBitCount = 32;
        bmi.biWidth = rect.bottomRightX - rect.topLeftX;
        bmi.biHeight = -rect.bottomRightY + rect.topLeftY;
        bmi.biCompression = BI_RGB;
        bmi.biSizeImage = 0;// 3 * rect.right * rect.bottom;
        img.create(rect.bottomRightY - rect.topLeftY, rect.bottomRightX - rect.topLeftX, CV_8UC4);
        GetDIBits(hDC, hBitmap, 0, rect.bottomRightY - rect.topLeftY, img.data, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
        DeleteObject(hBitmap);
        DeleteDC(hDC);
        ReleaseDC(NULL, hScreen);
    }
private:
    cv::Mat img;
    const Rect rect;
};

class TemplateMatcher {
public:
    TemplateMatcher(const std::string& filePath, Rect ssa = Rect(), bool grayscale = false)
    : grayscale(grayscale), 
        ss((ssa.bottomRightX == 0 && ssa.bottomRightY == 0) ? new ScreenShot() : new ScreenShot(ssa))
    {
        templateImg = cv::imread(filePath, grayscale ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
        if (templateImg.empty()) {
            throw std::runtime_error("Could not open or find the template image!");
        }
    }

    bool match(double tolerance, cv::Point* center = nullptr) const {
        cv::Mat img = grayscale ? ss->screenshotGreyScale() : ss->screenshotColour();

        cv::Mat result;
        // Create the result matrix
        int result_cols = img.cols - templateImg.cols + 1;
        int result_rows = img.rows - templateImg.rows + 1;
        result.create(result_rows, result_cols, CV_32FC1);
        // Perform template matching
        matchTemplate(img, templateImg, result, cv::TM_CCORR_NORMED);

        double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

#ifdef _DEBUG
        std::cout << maxVal << std::endl;
#endif
        if (maxVal > tolerance) {
            // Add half of the template's dimensions to maxLoc to find the center
            if (center) {
                *center = cv::Point(maxLoc.x + templateImg.cols / 2, maxLoc.y + templateImg.rows / 2);
                (*center).x += ss->getRect().topLeftX;
                (*center).y += ss->getRect().topLeftY;
            }
            return true;
        }

        return false;
    }
private:
    cv::Mat templateImg;
    bool grayscale;
    std::unique_ptr<ScreenShot> ss;
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

    auto target = std::make_unique<TemplateMatcher>("images/target1.png", Rect(391, 245, 999, 671));

    while (run.load()) {     
        cv::Point center;
        if (target->match(0.96, &center)) {
            //std::cout << center.x << ", " << center.y << std::endl;
            ClickScreen(center.x, center.y);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }

    checker.stopChecking();

    return 0;
}