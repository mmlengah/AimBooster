#include "ColorSelector.h"
#include <iostream>
#include <iomanip>

ColorSelector::ColorSelector(RGBColor targetColor, RGBColor markColor, int radius)
    : targetColor(targetColor), markColor(markColor), radius(radius),
    matchingPixels(std::make_shared<std::queue<Position>>()) {}

void ColorSelector::markSurroundingPixels(std::vector<RGBQUAD>& pixels, int x, int y, int width, int height) {
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            // Continue if the current position is outside the circle defined by the radius
            if (dx * dx + dy * dy > radius * radius) continue;

            int nx = x + dx;
            int ny = y + dy;

            // Continue if the new position is out of bounds
            if (nx < 0 || nx >= width || ny < 0 || ny >= height) continue;

            RGBQUAD& pixel = pixels[ny * width + nx];

            // Continue if the pixel is already the mark color
            if (pixel.rgbRed == markColor.r() && pixel.rgbGreen == markColor.g() && pixel.rgbBlue == markColor.b()) continue;

            // Mark the pixel with the color
            pixel.rgbRed = markColor.r();
            pixel.rgbGreen = markColor.g();
            pixel.rgbBlue = markColor.b();
            pixel.rgbReserved = 0;
        }
    }
}


void ColorSelector::processBitmap(HBitmap::HBitmapSharedPtr bmp, const RECT& captureArea) {
    if (!bmp || !*bmp) return;

    BITMAP bm{};
    GetObject(*bmp, sizeof(bm), &bm);

    HDC hdcScreen = GetDC(NULL);
    HDC hdc = CreateCompatibleDC(hdcScreen);
    ReleaseDC(NULL, hdcScreen);

    HBITMAP oldbmp = (HBITMAP)SelectObject(hdc, *bmp);

    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bm.bmWidth;
    bmi.bmiHeader.biHeight = -bm.bmHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    std::vector<RGBQUAD> pixels(bm.bmWidth * abs(bm.bmHeight));

    if (GetDIBits(hdc, *bmp, 0, abs(bm.bmHeight), pixels.data(), &bmi, DIB_RGB_COLORS)) {
        for (int y = 0; y < abs(bm.bmHeight); y++) {
            for (int x = 0; x < bm.bmWidth; x++) {
                int index = y * bm.bmWidth + x;
                RGBQUAD& quad = pixels[index];
                RGBColor currentTargetColor = targetColor; 

                if (quad.rgbRed == currentTargetColor.r() && quad.rgbGreen == currentTargetColor.g() && quad.rgbBlue == currentTargetColor.b()) {
                    matchingPixels->push(Position(x + captureArea.left, y + captureArea.top));
                    markSurroundingPixels(pixels, x, y, bm.bmWidth, abs(bm.bmHeight));
                }
            }
        }

        SetDIBits(hdc, *bmp, 0, abs(bm.bmHeight), pixels.data(), &bmi, DIB_RGB_COLORS);
    }

    SelectObject(hdc, oldbmp);
    DeleteDC(hdc);
}

std::shared_ptr<std::queue<Position>> ColorSelector::getMatchingPixels() {
    return matchingPixels;
}
