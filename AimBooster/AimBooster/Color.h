#pragma once
#include <windows.h>
#include <iostream>

struct RGBColor {
    RGBQUAD rgbColor;

    RGBColor(unsigned char red, unsigned char green, unsigned char blue);
    RGBColor();

    unsigned char r() const;
    unsigned char g() const;
    unsigned char b() const;

    bool operator==(const RGBColor& other) const;
    bool operator!=(const RGBColor& other) const;

    friend std::ostream& operator<<(std::ostream& os, const RGBColor& color);
};
