#pragma once

#include <windows.h>
#include <memory> 
#include "HBitmap.h"

class ScreenCapture {
public:
    ScreenCapture(RECT captureArea = { 0, 0, -1, -1 });
    bool SaveBitmap();
    bool SaveBitmapToFile(LPCWSTR filename);
    bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename);
    HBitmap::HBitmapSharedPtr GetBitmap();
    RECT GetCaptureArea() const;
private:
    HBitmap::HBitmapSharedPtr hBitmap;
    RECT captureArea;
    bool isCaptureAreaSet = false;
};