#include "ScreenCapture.h"
#include <memory>


int main() {
    // Create a unique_ptr to a new ScreenCapture instance
    std::unique_ptr<ScreenCapture> capturer = std::make_unique<ScreenCapture>();
    capturer->CaptureScreenToFile(L"screenshot.bmp");

    return 0;
}
