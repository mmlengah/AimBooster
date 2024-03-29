#include "ScreenCapture.h"
#include "ColorSelector.h"
#include "Color.h"
#include <memory>

int main() {
    RGBColor targetColor = RGBColor(12, 12, 12); // dark grey
    RGBColor markColor = RGBColor(0, 0, 255);  // Blue

    std::unique_ptr<ScreenCapture> capturer = std::make_unique<ScreenCapture>(RECT{ 0, 100, 1000, 200 });
    std::unique_ptr<ColorSelector> colorSelector = std::make_unique<ColorSelector>(targetColor, markColor, 5);

    capturer->SaveBitmap();
    colorSelector->processBitmap(capturer->GetBitmap(), capturer->GetCaptureArea());
    capturer->SaveBitmapToFile(L"Screenshot.bmp");

    return 0;
}
