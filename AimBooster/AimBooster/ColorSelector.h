#pragma once

#include <windows.h>
#include <queue>
#include <memory> 

struct Position {
    int x, y;
    Position(int x, int y) : x(x), y(y) {}
};

class ColorSelector {
public:
    ColorSelector(COLORREF color);
    void setBitmap(std::shared_ptr<HBITMAP> bmp);
    void processBitmap();
    std::shared_ptr<std::queue<Position>> getMatchingPixels() const;

private:
    std::shared_ptr<HBITMAP> hBitmap;
    COLORREF targetColor;
    std::shared_ptr<std::queue<Position>> matchingPixels;
};
