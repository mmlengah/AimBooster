#include "ApplicationStopper.h"
#include "ScreenCapture.h"
#include "ColorSelector.h"
#include "MouseClickSimulator.h"
#include "Color.h"
#include "InputHandler.h"
#include <memory>

int main() {
    InputHandler::getInstance().startListening();

    RGBColor targetColor = RGBColor(255, 219, 195); // light peach
    RGBColor markColor = RGBColor(0, 36, 60);  // dark blue

    std::unique_ptr<ApplicationStopper> app = std::make_unique<ApplicationStopper>();
    std::unique_ptr<ScreenCapture> capturer = std::make_unique<ScreenCapture>(RECT{ 861, 504, 1759, 1135 });
    std::unique_ptr<ColorSelector> colorSelector = std::make_unique<ColorSelector>(targetColor, markColor, 50);
    std::unique_ptr<MouseClickSimulator> simulator = std::make_unique<MouseClickSimulator>();

    while (app->isRunning()) {
        capturer->SaveBitmap();
        colorSelector->processBitmap(capturer->GetBitmap(), capturer->GetCaptureArea());
        //capturer->SaveBitmapToFile(L"ScreenShot.bmp");
        simulator->click(colorSelector->getMatchingPixels(), app->isRunning());
    }

    InputHandler::getInstance().stopListening();
    return 0;
}