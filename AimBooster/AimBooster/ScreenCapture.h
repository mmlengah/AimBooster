#pragma once

#include <windows.h>
#include <memory> 

struct HBitmapDeleter {
    void operator()(HBITMAP* ptr) {
        if (ptr && *ptr) {
            DeleteObject(*ptr);
            delete ptr;
        }
    }
};

class ScreenCapture {
public:
    ScreenCapture();
    bool CaptureScreen(); 
    bool CaptureScreenToFile(LPCWSTR filename); 
    bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename);
    std::shared_ptr<HBITMAP> GetBitmap() const;
private:
    std::shared_ptr<HBITMAP> hBitmapPtr;
    static void DeleteObjectFunc(HGDIOBJ obj); 
};