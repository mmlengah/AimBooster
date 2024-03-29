#pragma once

#include <windows.h>
#include <memory> 
#include "HBitmap.h"

class ScreenCapture {
public:
    ScreenCapture();
    bool SaveBitmap();
    bool SaveBitmapToFile(LPCWSTR filename); 
    bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename);
    HBitmap::HBitmapSharedPtr GetBitmap();
private:
    HBitmap::HBitmapSharedPtr hBitmap;
};