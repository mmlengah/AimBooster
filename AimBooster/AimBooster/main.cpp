#include "ScreenCapture.h"
#include <memory>


int main() {
    std::unique_ptr<ScreenCapture> capturer = std::make_unique<ScreenCapture>();
    capturer->CaptureScreen();
    std::shared_ptr<HBITMAP> a = capturer->GetBitmap();
    capturer->SaveBitmapToFile(*(a), L"Screenshot.bmp");

    return 0;
}
