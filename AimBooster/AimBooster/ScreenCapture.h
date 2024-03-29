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
    static int GetScreenWidth();
    static int GetScreenHeight();
private:
    static void InitializeScreenDimensions();
    inline static int screenWidth = 0;
    inline static int screenHeight = 0;
    inline static bool staticDimensionsSet = false;
    HBitmap::HBitmapSharedPtr hBitmap;
    RECT captureArea;
    bool isCaptureAreaSet = false;
};