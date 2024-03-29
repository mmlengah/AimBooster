#pragma once

#include <windows.h>
#include <memory> 
#include "HBitmapPointer.h"

class ScreenCapture {
public:
    ScreenCapture();
    bool SaveBitmap();
    bool SaveBitmapToFile(LPCWSTR filename); 
    bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename);
    HBitmapSharedPtr& GetBitmap();
private:
    HBitmapSharedPtr hBitmapPtr;
};