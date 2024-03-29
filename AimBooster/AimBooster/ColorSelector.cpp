#include "ColorSelector.h"
#include <iostream>
#include <iomanip>

ColorSelector::ColorSelector(Color targetColor, Color markColor, int radius) : targetColor(targetColor),
markColor(markColor), radius(radius), matchingPixels(std::make_shared<std::queue<Position>>()) {}

void ColorSelector::markSurroundingPixels(std::vector<Color>& pixels, int x, int y, int width, int height) {
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height && pixels[ny * width + nx] != markColor) {
                    pixels[ny * width + nx] = markColor;
                }
            }
        }
    }
}

void ColorSelector::processBitmap(HBitmap::HBitmapSharedPtr bmp) {
    if (!bmp || !*bmp) return;

    BITMAP bm{};
    
    GetObject(*bmp, sizeof(bm), &bm); // Retrieve bitmap information

    // Create a compatible DC
    HDC hdcScreen = GetDC(NULL);
    HDC hdc = CreateCompatibleDC(hdcScreen);
    ReleaseDC(NULL, hdcScreen);

    // Select the bitmap into the compatible DC
    HBITMAP oldbmp = (HBITMAP)SelectObject(hdc, *bmp);

    // Prepare to retrieve the bitmap's pixels
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bm.bmWidth;
    bmi.bmiHeader.biHeight = -bm.bmHeight; // Modify to ensure top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // Assuming 32-bit bitmap for simplicity
    bmi.bmiHeader.biCompression = BI_RGB;

    // Allocate memory for the pixels
    auto pixels = new RGBQUAD[bm.bmWidth * abs(bm.bmHeight)];

    // Get the bitmap's pixels
    if (GetDIBits(hdc, *bmp, 0, abs(bm.bmHeight), pixels, &bmi, DIB_RGB_COLORS)) {
        std::vector<Color> pixelColors(bm.bmWidth * abs(bm.bmHeight)); // To store and modify colors
        for (int y = 0; y < abs(bm.bmHeight); y++) {
            for (int x = 0; x < bm.bmWidth; x++) {
                // Calculate the pixel's index in the buffer
                int index = y * bm.bmWidth + x;
                RGBQUAD& quad = pixels[index];
                Color currentColor(quad.rgbBlue, quad.rgbGreen, quad.rgbRed);

                pixelColors[index] = currentColor; // Store the original color

                if (currentColor == targetColor) {
                    matchingPixels->push(Position(x, y)); // Store matching pixel position
                    markSurroundingPixels(pixelColors, x, y, bm.bmWidth, abs(bm.bmHeight)); // Mark surrounding pixels
                }
            }
        }

        // Convert modified pixelColors back to RGBQUAD array
        for (int i = 0; i < bm.bmWidth * abs(bm.bmHeight); i++) {
            pixels[i].rgbBlue = pixelColors[i].b;
            pixels[i].rgbGreen = pixelColors[i].g;
            pixels[i].rgbRed = pixelColors[i].r;
        }

        // Update the bitmap with the modified pixels
        SetDIBits(hdc, *bmp, 0, abs(bm.bmHeight), pixels, &bmi, DIB_RGB_COLORS);
    }

    // Cleanup
    delete[] pixels;
    SelectObject(hdc, oldbmp); // Restore the old bitmap
    DeleteDC(hdc); // Delete the DC
}

std::shared_ptr<std::queue<Position>> ColorSelector::getMatchingPixels() const {
    return matchingPixels;
}