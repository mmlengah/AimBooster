#include "ColorSelector.h"

ColorSelector::ColorSelector(COLORREF color) : hBitmap(nullptr), targetColor(color), matchingPixels(std::make_shared<std::queue<Position>>()) {}

void ColorSelector::setBitmap(std::shared_ptr<HBITMAP> bmp) {
    hBitmap = bmp;
}

void ColorSelector::processBitmap() {
    if (!hBitmap || !*hBitmap) return;

    BITMAP bm;
    GetObject(*hBitmap, sizeof(BITMAP), &bm);
    HDC hdc = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP oldbmp = (HBITMAP)SelectObject(hdcMem, *hBitmap);

    for (int y = 0; y < bm.bmHeight; y++) {
        for (int x = 0; x < bm.bmWidth; x++) {
            COLORREF pixelColor = GetPixel(hdcMem, x, y);
            if (pixelColor == targetColor) {
                matchingPixels->push(Position(x, y));
            }
        }
    }

    SelectObject(hdcMem, oldbmp);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdc);
}

std::shared_ptr<std::queue<Position>> ColorSelector::getMatchingPixels() const {
    return matchingPixels;
}
