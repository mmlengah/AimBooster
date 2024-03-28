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
    ColorSelector(COLORREF color, COLORREF markColor, int radius);
    void processBitmap(std::shared_ptr<HBITMAP> bmp);
    std::shared_ptr<std::queue<Position>> getMatchingPixels() const;
private:
    COLORREF targetColor;
    COLORREF markColor;
    int radius;
    std::shared_ptr<std::queue<Position>> matchingPixels;

    void markSurroundingPixels(std::vector<COLORREF>& pixels, int x, int y, int width, int height);
};