//#include "ColorSelector.h"
//
//ColorSelector::ColorSelector(COLORREF color, COLORREF markColor, int radius) : targetColor(color), markColor(markColor), radius(radius), matchingPixels(std::make_shared<std::queue<Position>>()) {}
//
//void ColorSelector::markSurroundingPixels(std::vector<COLORREF>& pixels, int x, int y, int width, int height) {
//    for (int dy = -radius; dy <= radius; dy++) {
//        for (int dx = -radius; dx <= radius; dx++) {
//            if (dx * dx + dy * dy <= radius * radius) {
//                int nx = x + dx;
//                int ny = y + dy;
//                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
//                    pixels[ny * width + nx] = markColor;
//                }
//            }
//        }
//    }
//}
//
//void ColorSelector::processBitmap(std::shared_ptr<HBITMAP> bmp) {
//    if (!bmp || !*bmp) return;
//
//    BITMAP bm;
//    GetObject(*bmp, sizeof(BITMAP), &bm);
//
//    BITMAPINFOHEADER bi = { 0 };
//    bi.biSize = sizeof(BITMAPINFOHEADER);
//    bi.biWidth = bm.bmWidth;
//    bi.biHeight = -bm.bmHeight;
//    bi.biPlanes = 1;
//    bi.biBitCount = 32; 
//    bi.biCompression = BI_RGB;
//
//    std::vector<COLORREF> pixels(bm.bmWidth * bm.bmHeight);
//    HDC hdc = GetDC(NULL);
//    GetDIBits(hdc, *bmp, 0, bm.bmHeight, pixels.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
//
//    
//
//    SetDIBits(hdc, *bmp, 0, bm.bmHeight, pixels.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
//    ReleaseDC(NULL, hdc);
//}
//
//void ColorSelector::processBitmap(std::shared_ptr<HBITMAP>& bmp) {
//    if (!bmp || !*bmp) return;
//
//    BITMAP bm;
//    GetObject(*bmp, sizeof(BITMAP), &bm);
//
//    BITMAPINFOHEADER bi = { 0 };
//    bi.biSize = sizeof(BITMAPINFOHEADER);
//    bi.biWidth = bm.bmWidth;
//    bi.biHeight = -bm.bmHeight; // negative to indicate top-down bitmap
//    bi.biPlanes = 1;
//    bi.biBitCount = 32;
//    bi.biCompression = BI_RGB;
//
//    std::vector<COLORREF> pixels(bm.bmWidth * bm.bmHeight);
//    HDC hdcSource = GetDC(NULL);
//    GetDIBits(hdcSource, *bmp, 0, bm.bmHeight, pixels.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
//
//    // Create a compatible DC and a new bitmap where modifications will be applied
//    HDC hdcTarget = CreateCompatibleDC(hdcSource);
//    HBITMAP newBmp = CreateCompatibleBitmap(hdcSource, bm.bmWidth, bm.bmHeight);
//    SelectObject(hdcTarget, newBmp);
//
//    for (int y = 0; y < bm.bmHeight; y++) {
//        for (int x = 0; x < bm.bmWidth; x++) {
//            COLORREF& pixelColor = pixels[y * bm.bmWidth + x];
//            if (pixelColor == targetColor) {
//                matchingPixels->push(Position(x, y));
//                markSurroundingPixels(pixels, x, y, bm.bmWidth, bm.bmHeight);
//            }
//        }
//    }
//
//    // Apply the modifications by setting the pixels to the new bitmap
//    SetDIBits(hdcTarget, newBmp, 0, bm.bmHeight, pixels.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
//
//    bmp = std::shared_ptr<HBITMAP>(new HBITMAP(bm), HBitmapDeleter());
//
//    // Clean up
//    ReleaseDC(NULL, hdcSource);
//    DeleteDC(hdcTarget);
//}
//
//
//std::shared_ptr<std::queue<Position>> ColorSelector::getMatchingPixels() const {
//    return matchingPixels;
//}