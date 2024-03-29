#pragma once

#include <windows.h>
#include <memory>

namespace HBitmap {
    struct HBitmapDeleter {
        void operator()(HBITMAP* ptr) {
            if (ptr && *ptr) {
                DeleteObject(*ptr);
                delete ptr;
            }
        }
    };

    using HBitmapSharedPtr = std::shared_ptr<HBITMAP>;

    inline HBitmapSharedPtr MakeHBitmapSharedPtr(HBITMAP hBitmap) {
        return HBitmapSharedPtr(new HBITMAP(hBitmap), HBitmapDeleter());
    }
}


