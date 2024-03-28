#pragma once

#include <windows.h>

class ScreenCapture {
public:
    ScreenCapture();
    bool CaptureScreenToFile(LPCWSTR filename);

private:
    bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename);
};
