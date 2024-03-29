#include "ScreenCapture.h"
#include <shellscalingapi.h>

#pragma comment(lib, "Shcore.lib")

ScreenCapture::ScreenCapture(RECT captureArea) : hBitmap(nullptr), captureArea(captureArea) {
    SetProcessDPIAware();
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    if (captureArea.right <= captureArea.left || captureArea.bottom <= captureArea.top ||
        captureArea.left < 0 || captureArea.top < 0 ||
        captureArea.right > screenWidth || captureArea.bottom > screenHeight) {
        this->captureArea = { 0, 0, screenWidth, screenHeight };
        isCaptureAreaSet = false;
    }
    else {
        isCaptureAreaSet = true;
    }
}

bool ScreenCapture::SaveBitmap() {
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    int width = isCaptureAreaSet ? captureArea.right - captureArea.left : GetSystemMetrics(SM_CXSCREEN);
    int height = isCaptureAreaSet ? captureArea.bottom - captureArea.top : GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hRawBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hRawBitmap);

    int captureX = isCaptureAreaSet ? captureArea.left : 0;
    int captureY = isCaptureAreaSet ? captureArea.top : 0;
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, captureX, captureY, SRCCOPY);

    hBitmap = HBitmap::MakeHBitmapSharedPtr(hRawBitmap);

    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return hBitmap != nullptr;
}

bool ScreenCapture::SaveBitmapToFile(LPCWSTR filename) {
    if (!hBitmap || !(*hBitmap)) {
        return false; 
    }

    return SaveBitmapToFile(*hBitmap, filename);
}

HBitmap::HBitmapSharedPtr ScreenCapture::GetBitmap() {
    return hBitmap;
}

bool ScreenCapture::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename) {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    BITMAP bitmap{};
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

RECT ScreenCapture::GetCaptureArea() const {
    return captureArea;
}
