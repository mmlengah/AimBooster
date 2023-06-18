#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <functional>
#include <conio.h>
#include <vector>
#include <variant>

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

    static std::vector<cv::Vec3b> toVec3b(const std::vector<Color>& colors) {
        std::vector<cv::Vec3b> vecs;
        vecs.reserve(colors.size());
        for (const Color& color : colors) {
            vecs.push_back(color);  // uses overloaded operator
        }
        return vecs;
    }

    static std::vector<cv::Vec3b> toVec3b(const Color& color) {
        std::vector<cv::Vec3b> vecs;
        vecs.push_back(color);
        return vecs;
    }
};

class ClickPixel {
public:
    ClickPixel(std::variant<Color, std::vector<Color>> targetColors, Rect rect = Rect(), int radius = 1)
        : rect((rect.bottomRightX == 0 && rect.bottomRightY == 0) ?
            Rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)) : rect), radius(radius) {

        targetColor = std::holds_alternative<Color>(targetColors) ? 
            Color::toVec3b(std::get<Color>(targetColors)) : 
            Color::toVec3b(std::get<std::vector<Color>>(targetColors));

        if (!img) {
            img = std::make_unique<cv::Mat>();
        }
        if (!ss) {
            ss = std::make_unique<ScreenShot>();
        }
    }

    template <typename Func>
    void process(Func&& func) {
        // Loop through the image pixels within the specified rectangle
        for (int y = rect.topLeftY; y <= rect.bottomRightY; y++) {
            for (int x = rect.topLeftX; x <= rect.bottomRightX - targetColor.size(); x++) {
                bool allTrue = true;
                // Check if the pixel color matches the given color
                for (int index = 0; index < targetColor.size(); ++index) {
                    if (!isPixelColor(x + index, y, targetColor[index])) {
                        allTrue = false;
                        break;
                    }
                }
                
                if (allTrue) {
                    //lambda function here that can use x and y
                    func(x, y);

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
                bool allTrue = true;
                // Check if the pixel color matches the given color
                for (int index = 0; index < targetColor.size(); ++index) {
                    if (!isPixelColor(x + index, y, targetColor[index])) {
                        allTrue = false;
                        break;
                    }
                }

                if (allTrue) {
                    //lambda function here that can use x and y
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
    std::vector<cv::Vec3b> targetColor;
    int radius;
    const Rect rect;
    static inline std::unique_ptr<cv::Mat> img = nullptr;
    static inline std::unique_ptr<ScreenShot> ss = nullptr;

    bool isPixelColor(int x, int y, cv::Vec3b color) {
        return img->at<cv::Vec3b>(y, x) == color;
    }
};

void checkForExit(std::atomic<bool>& running) {
    while (running) {
        if (_kbhit()) {
            int key = _getch();
            // If the user presses the Escape key (ASCII value is 27), stop the program
            if (key == 27) { 
                running = false;
            }
        }
    }
}

std::function<void(int, int)> clickScreen = [](int x, int y) {
    // Set the mouse position
    SetCursorPos(x + 3, y);

    // Simulate a left mouse button down event
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    // Simulate a left mouse button up event
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
};

int main() {
    Sleep(1000);
    std::atomic<bool> run(true);
    std::thread exitThread(checkForExit, std::ref(run));
    
    std::vector<Color> colors = { Color(255,219,195), Color(255,219,195),  Color(255,219,195),  Color(255,219,195) };
    ClickPixel target(colors, Rect(392, 243, 1002, 674), 15);
    
    while (run.load()) {    
        ClickPixel::take();
        target.process(clickScreen);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    exitThread.join();

    return 0;
}