#include <windows.h>
#include <shellscalingapi.h>

// Ensure to link against Shcore.lib; add it in your project settings or use:
#pragma comment(lib, "Shcore.lib")

bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR filename) {
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

    imageSize = bitmap.bmWidth * bitmap.bmHeight * 4; // Assuming 4 bytes per pixel (32 bits)
    imageData = new char[imageSize];

    ZeroMemory(&fileHeader, sizeof(fileHeader));
    fileHeader.bfType = 0x4D42; // 'BM' for Bitmap
    fileHeader.bfSize = sizeof(fileHeader) + sizeof(infoHeader) + imageSize;
    fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader);

    ZeroMemory(&infoHeader, sizeof(infoHeader));
    infoHeader.biSize = sizeof(infoHeader);
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 32; // Assuming 32 bits per pixel
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

int main() {
    // Make the process DPI aware to capture the full resolution on high-DPI displays
    SetProcessDPIAware();

    // Now that we're DPI aware, obtain the screen's actual resolution
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
    SaveBitmapToFile(hBitmap, L"screenshot.bmp");
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return 0;
}
