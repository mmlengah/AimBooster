#pragma once

#include <windows.h>
#include <memory> 
#include "HBitmapPointer.h"

class ScreenCapture {
public:
    ScreenCapture();
    bool CaptureScreen(); 
    bool CaptureScreenToFile(LPCWSTR filename); 
    bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename);
    HBitmapSharedPtr GetBitmap() const;
private:
    HBitmapSharedPtr hBitmapPtr;
};