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
            Rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)) : rect) {}

    cv::Mat captureScreen() {
        capture();
        cv::Mat img3;
        cv::cvtColor(std::move(img), img3, cv::COLOR_BGRA2BGR);
        return img3;
    }

    void display() {
        cv::Mat dispImg = captureScreen();
        const std::string windowName = "Display window";
        cv::namedWindow(windowName, cv::WINDOW_NORMAL);
        cv::resizeWindow(windowName, 600, 400);
        cv::moveWindow(windowName, 0, 0);
        cv::imshow(windowName, std::move(dispImg));
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
        BITMAPINFOHEADER bmi = { sizeof(BITMAPINFOHEADER), rect.bottomRightX - rect.topLeftX, -rect.bottomRightY + rect.topLeftY, 1, 32, BI_RGB, 0 };
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
    {
        if (ss == nullptr) {
            ss = std::make_unique<ScreenShot>((ssa.bottomRightX == 0 && ssa.bottomRightY == 0) ?
                Rect() : ssa);
            img = ss->captureScreen();
        }

        templateImg = cv::imread(filePath, grayscale ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
        if (templateImg.empty()) {
            throw std::runtime_error("Could not open or find the template image!");
        }
    }

    static void takess(bool grayscale = false) {
        img = grayscale ? ss->screenshotGreyScale() : ss->captureScreen();
    }

    bool match(double tolerance, cv::Point* center = nullptr) const {     
        // Define a Region of Interest within the image
        cv::Rect roi(ss->getRect().topLeftX, ss->getRect().topLeftY,
            ss->getRect().bottomRightX - ss->getRect().topLeftX,
            ss->getRect().bottomRightY - ss->getRect().topLeftY);

        cv::Mat imgROI = img(roi);

        cv::Mat result;
        // Create the result matrix
        int result_cols = imgROI.cols - templateImg.cols + 1;
        int result_rows = imgROI.rows - templateImg.rows + 1;
        result.create(result_rows, result_cols, CV_32FC1);

        // Perform template matching
        matchTemplate(imgROI, templateImg, result, cv::TM_CCORR_NORMED);

        double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

#ifdef _DEBUG
        std::cout << maxVal << std::endl;
#endif
        if (maxVal > tolerance) {
            // Add half of the template's dimensions to maxLoc to find the center
            // Also add the top left coordinates of the ROI to account for the offset
            if (center) {
                *center = cv::Point(maxLoc.x + templateImg.cols / 2 + ss->getRect().topLeftX,
                    maxLoc.y + templateImg.rows / 2 + ss->getRect().topLeftY);
            }
            return true;
        }

        return false;
    }

private:
    cv::Mat templateImg;
    static inline cv::Mat img;
    static inline std::unique_ptr<ScreenShot> ss = nullptr;

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
        TemplateMatcher::takess();
        cv::Point center;
        if (target->match(0.96, &center)) {
            ClickScreen(center.x, center.y);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }

    checker.stopChecking();

    return 0;
}