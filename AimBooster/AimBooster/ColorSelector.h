#pragma once
#include "HBitmap.h"
#include "Color.h"
#include "Position.h"
#include <windows.h>
#include <queue>
#include <memory>
#include <vector>

class ColorSelector {
public:
    ColorSelector(RGBColor targetColor, RGBColor markColor, int radius);
    void processBitmap(HBitmap::HBitmapSharedPtr bmp);
    std::shared_ptr<std::queue<Position>> getMatchingPixels() const;
private:
    RGBColor targetColor;
    RGBColor markColor;
    int radius;
    std::shared_ptr<std::queue<Position>> matchingPixels;
    void markSurroundingPixels(std::vector<RGBQUAD>& pixels, int x, int y, int width, int height);
};
