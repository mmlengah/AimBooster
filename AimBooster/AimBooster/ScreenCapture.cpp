#include "ScreenCapture.h"
#include <shellscalingapi.h>

#pragma comment(lib, "Shcore.lib")

ScreenCapture::ScreenCapture() : hBitmapPtr(nullptr) {

}

bool ScreenCapture::CaptureScreen() {
    SetProcessDPIAware();

    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    hBitmapPtr = MakeHBitmapSharedPtr(HBITMAP(hBitmap));

    // Cleanup
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return hBitmapPtr != nullptr;
}

bool ScreenCapture::CaptureScreenToFile(LPCWSTR filename) {
    SetProcessDPIAware();

    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    hBitmapPtr = MakeHBitmapSharedPtr(HBITMAP(hBitmap));

    bool result = SaveBitmapToFile(hBitmap, filename);

    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return result;
}

std::shared_ptr<HBITMAP> ScreenCapture::GetBitmap() const {
    return hBitmapPtr;
}

bool ScreenCapture::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename) {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    BITMAP bitmap;
    DWORD write = 0;
    HANDLE fileHandle;
    DWORD imageSize;
    char* imageData;

    GetObject(hBitmap, sizeof(bitmap), &bitmap);

    fileHandle = CreateFileW(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        return false;
    }

    imageSize = bitmap.bmWidth * bitmap.bmHeight * 4; // Assuming 4 bytes per pixel
    imageData = new char[imageSize];

    ZeroMemory(&fileHeader, sizeof(fileHeader));
    fileHeader.bfType = 0x4D42; // 'BM'
    fileHeader.bfSize = sizeof(fileHeader) + sizeof(infoHeader) + imageSize;
    fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader);

    ZeroMemory(&infoHeader, sizeof(infoHeader));
    infoHeader.biSize = sizeof(infoHeader);
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 32; // 32 bits per pixel
    infoHeader.biWidth = bitmap.bmWidth;
    infoHeader.biHeight = bitmap.bmHeight;
    infoHeader.biCompression = BI_RGB;
    infoHeader.biSizeImage = imageSize;

    GetDIBits(GetDC(NULL), hBitmap, 0, bitmap.bmHeight, imageData, (BITMAPINFO*)&infoHeader, DIB_RGB_COLORS);

    WriteFile(fileHandle, &fileHeader, sizeof(fileHeader), &write, NULL);
    WriteFile(fileHandle, &infoHeader, sizeof(infoHeader), &write, NULL);
    WriteFile(fileHandle, imageData, imageSize, &write, NULL);

    delete[] imageData;
    CloseHandle(fileHandle);

    return true;
}
