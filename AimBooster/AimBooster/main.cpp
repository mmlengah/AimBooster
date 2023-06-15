#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <chrono>

struct Rect {
    int topLeftX;
    int topLeftY;
    int bottomRightX;
    int bottomRightY;

    Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
        : topLeftX(x1), topLeftY(y1), bottomRightX(x2), bottomRightY(y2) {
    }

    int getWidth() const {
        return bottomRightX - topLeftX + 1;
    }

    int getHeight() const {
        return bottomRightY - topLeftY + 1;
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
    const Rect rect;
    cv::Mat img;
};

struct Color {
    int red;
    int green;
    int blue;

    Color(int r = 0, int g = 0, int b = 0) {
        red = (r >= 0 && r <= 255) ? r : 0;
        green = (g >= 0 && g <= 255) ? g : 0;
        blue = (b >= 0 && b <= 255) ? b : 0;
    }

    operator cv::Vec3b() const {
        return cv::Vec3b(blue, green, red);
    }
};


class ClickPixel {
public:
    ClickPixel(Color targetColor, Rect rect = Rect(), int radius = 1)
        : targetColor(targetColor), rect((rect.bottomRightX == 0 && rect.bottomRightY == 0) ?
            Rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)) : rect), radius(radius) {
        if (!img) {
            img = std::make_unique<cv::Mat>();
        }
        if (!ss) {
            ss = std::make_unique<ScreenShot>();
        }
    }

    void process() {
        // Loop through the image pixels within the specified rectangle
        for (int y = rect.topLeftY; y <= rect.bottomRightY; y++) {
            for (int x = rect.topLeftX; x <= rect.bottomRightX; x++) {
                // Check if the pixel color matches the given color
                if (isPixelColor(x, y)) {
                    clickScreen(x, y);

                    // Skip the next 'radius' pixels in both directions
                    x += radius;
                    y += radius;
                }
            }
        }
    }


    void show(bool fullsize = false) {
        // Start the timer
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        // Define ROI
        cv::Rect roi(rect.topLeftX, rect.topLeftY, rect.getWidth(), rect.getHeight());

        // Create a mask the same size as the ROI, all white (i.e., unmasked)
        cv::Mat mask = cv::Mat::ones(roi.size(), CV_8U) * 255;

        // Create an image for the ROI with the same size as the ROI
        cv::Mat roi_img = cv::Mat::zeros(roi.size(), img->type());

        // Copy the ROI from the original image to the new image using the mask
        img->operator()(roi).copyTo(roi_img, mask);

        for (int y = 0; y < roi_img.rows; y++) {
            for (int x = 0; x < roi_img.cols; x++) {
                // Check if the pixel color matches the given color                
                if (isPixelColor(x + rect.topLeftX, y + rect.topLeftY)) {
                    roi_img.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 0, 0);
                    // Skip the next 'radius' pixels in both directions
                    x += radius;
                    y += radius;
                }
            }
        }

        // Stop the timer
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        // Calculate the elapsed time in milliseconds
        double elapsedTime = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

        std::cout << "Processing time: " << elapsedTime << " ms" << std::endl;


        // Resize the image
        if (!fullsize) {
            cv::resize(roi_img, roi_img, cv::Size(640, 480));
        }

        // Display the ROI image
        cv::imshow("ROI Image", roi_img);
        cv::waitKey(0);
    }

    static void take() {
        cv::Mat tempMat = ss->captureScreen();
        img = std::make_unique<cv::Mat>(tempMat.clone());
    }
private:
    cv::Vec3b targetColor;
    int radius;
    const Rect rect;
    static inline std::unique_ptr<cv::Mat> img = nullptr;
    static inline std::unique_ptr<ScreenShot> ss = nullptr;

    bool isPixelColor(int x, int y) {
        return img->at<cv::Vec3b>(y, x) == targetColor;
    }

    void clickScreen(int x, int y) {
        // Set the mouse position
        SetCursorPos(x, y);

        // Simulate a left mouse button down event
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

        // Simulate a left mouse button up event
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
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


int main() {
    Sleep(1000);
    std::atomic<bool> run(true);
    EscapeKeyChecker checker(run);
    checker.startChecking();
    
    ClickPixel target(Color(255, 219, 195), Rect(392, 243, 1002, 674), 15);
    
    while (run.load()) {    
        ClickPixel::take();
        target.process();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    checker.stopChecking();

    return 0;
}