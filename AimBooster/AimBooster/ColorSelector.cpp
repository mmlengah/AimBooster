#include "ColorSelector.h"

ColorSelector::ColorSelector(COLORREF color, COLORREF markColor, int radius) : targetColor(color), markColor(markColor), radius(radius), matchingPixels(std::make_shared<std::queue<Position>>()) {}

void ColorSelector::markSurroundingPixels(std::vector<COLORREF>& pixels, int x, int y, int width, int height) {
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    pixels[ny * width + nx] = markColor;
                }
            }
        }
    }
}

void ColorSelector::processBitmap(std::shared_ptr<HBITMAP> bmp) {
    if (!bmp || !*bmp) return;

    BITMAP bm;
    GetObject(*bmp, sizeof(BITMAP), &bm);

    BITMAPINFOHEADER bi = { 0 };
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bm.bmWidth;
    bi.biHeight = -bm.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32; 
    bi.biCompression = BI_RGB;

    std::vector<COLORREF> pixels(bm.bmWidth * bm.bmHeight);
    HDC hdc = GetDC(NULL);
    GetDIBits(hdc, *bmp, 0, bm.bmHeight, pixels.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    for (int y = 0; y < bm.bmHeight; y++) {
        for (int x = 0; x < bm.bmWidth; x++) {
            COLORREF& pixelColor = pixels[y * bm.bmWidth + x];
            if (pixelColor == targetColor) {
                matchingPixels->push(Position(x, y));
                markSurroundingPixels(pixels, x, y, bm.bmWidth, bm.bmHeight);
            }
        }
    }

    SetDIBits(hdc, *bmp, 0, bm.bmHeight, pixels.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    ReleaseDC(NULL, hdc);
}

std::shared_ptr<std::queue<Position>> ColorSelector::getMatchingPixels() const {
    return matchingPixels;
}