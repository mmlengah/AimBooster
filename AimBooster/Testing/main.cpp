#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>


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

        // Resize the window to match the image size.
        cv::resizeWindow(windowName, dispImg.cols, dispImg.rows);

        // Move the window to the top left of the screen.
        cv::moveWindow(windowName, 0, 0);

        // Show our image inside the window.
        cv::imshow(windowName, dispImg);

        // Wait for a keystroke in the window
        cv::waitKey(0);
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

// Function to perform template matching
cv::Mat templateMatch(const cv::Mat& img, const cv::Mat& templateImg) {
    cv::Mat result;

    // Create the result matrix
    int result_cols = img.cols - templateImg.cols + 1;
    int result_rows = img.rows - templateImg.rows + 1;

    result.create(result_rows, result_cols, CV_32FC1);

    // Perform template matching
    matchTemplate(img, templateImg, result, cv::TM_CCORR_NORMED);

    return result;
}

int main() {

    ScreenShot ss(Rect(391, 245, 999, 671));
    // Load source image and template
    Sleep(1000);
    
    cv::Mat templateImg = cv::imread("images/target1.png", cv::IMREAD_COLOR);

    //if (img.empty() || templateImg.empty()) {
    //    std::cout << "Can't read one of the images" << std::endl;
    //    return -1;
    //}

    while (true) {
        cv::Mat img = ss.screenshotColour();
        cv::Mat result = templateMatch(img, templateImg);

        // Localizing the best match with minMaxLoc
        double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

        std::cout << maxVal << std::endl;
    }
    
    // Create the rectangle object to visualize the match
    //rectangle(img, maxLoc, cv::Point(maxLoc.x + templateImg.cols, maxLoc.y + templateImg.rows), cv::Scalar::all(0), 2, 8, 0);
    //rectangle(result, maxLoc, cv::Point(maxLoc.x + templateImg.cols, maxLoc.y + templateImg.rows), cv::Scalar::all(0), 2, 8, 0);

    //// Display the result
    //cv::namedWindow("Source Image", cv::WINDOW_NORMAL);
    //cv::imshow("Source Image", img);
    //cv::resizeWindow("Source Image", 600, 400); 

    //cv::namedWindow("Result Window", cv::WINDOW_NORMAL);
    //cv::imshow("Result Window", result);
    //cv::resizeWindow("Result Window", 600, 400);  

    // Wait until user exits the program
    //cv::waitKey(0);

    return 0;
}

