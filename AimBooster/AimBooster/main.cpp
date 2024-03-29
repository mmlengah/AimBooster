#include "ScreenCapture.h"
#include "ColorSelector.h"
#include <memory>


int main() {
    COLORREF targetColor = RGB(28, 28, 28); // Dark gray
    COLORREF markColor = RGB(255, 0, 0);  // Red

    std::unique_ptr<ScreenCapture> capturer = std::make_unique<ScreenCapture>();
    std::unique_ptr<ColorSelector> colorSelector = std::make_unique<ColorSelector>(targetColor, markColor, 5);

    capturer->SaveBitmap();
    colorSelector->processBitmap(capturer->GetBitmap());
    capturer->SaveBitmapToFile(L"Screenshot.bmp");

    return 0;
}
