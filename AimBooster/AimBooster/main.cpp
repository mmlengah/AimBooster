#include "ScreenCapture.h"
#include "ColorSelector.h"
#include <memory>


int main() {
    Color targetColor = Color(72, 64, 192); // dark grey
    Color markColor = Color(255, 0, 0);  // Red

    std::unique_ptr<ScreenCapture> capturer = std::make_unique<ScreenCapture>();
    std::unique_ptr<ColorSelector> colorSelector = std::make_unique<ColorSelector>(targetColor, markColor, 5);

    capturer->SaveBitmap();
    colorSelector->processBitmap(capturer->GetBitmap());
    capturer->SaveBitmapToFile(L"Screenshot.bmp");

    return 0;
}
