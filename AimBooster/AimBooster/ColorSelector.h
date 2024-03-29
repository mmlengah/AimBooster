#include "Color.h"
#include "HBitmap.h"
#include <windows.h>
#include <queue>
#include <memory>
#include <vector>

struct Position {
    int x, y;
    Position(int x, int y) : x(x), y(y) {}
};

class ColorSelector {
public:
    ColorSelector(Color targetColor, Color markColor, int radius);
    void processBitmap(HBitmap::HBitmapSharedPtr bmp);
    std::shared_ptr<std::queue<Position>> getMatchingPixels() const;
private:
    Color targetColor;
    Color markColor;
    int radius;
    std::shared_ptr<std::queue<Position>> matchingPixels;
    void markSurroundingPixels(std::vector<Color>& pixels, int x, int y, int width, int height);
};