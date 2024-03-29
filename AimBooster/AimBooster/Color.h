#pragma once
#include <windows.h>
#include <iostream>

struct RGBColor {
    RGBQUAD rgbColor;

    RGBColor(unsigned char red, unsigned char green, unsigned char blue) {
        rgbColor.rgbRed = red;
        rgbColor.rgbGreen = green;
        rgbColor.rgbBlue = blue;
        rgbColor.rgbReserved = 0; 
    }

    RGBColor() {
        rgbColor.rgbBlue = 0;
        rgbColor.rgbGreen = 0;
        rgbColor.rgbRed = 0;
        rgbColor.rgbReserved = 0;
    }

    unsigned char r() const { return rgbColor.rgbRed; }
    unsigned char g() const { return rgbColor.rgbGreen; }
    unsigned char b() const { return rgbColor.rgbBlue; }

    bool operator==(const RGBColor& other) const {
        return rgbColor.rgbRed == other.rgbColor.rgbRed
            && rgbColor.rgbGreen == other.rgbColor.rgbGreen
            && rgbColor.rgbBlue == other.rgbColor.rgbBlue;
    }

    bool operator!=(const RGBColor& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const RGBColor& color) {
        os << "R: " << static_cast<int>(color.rgbColor.rgbRed) << " "
            << "G: " << static_cast<int>(color.rgbColor.rgbGreen) << " "
            << "B: " << static_cast<int>(color.rgbColor.rgbBlue);
        return os;
    }
};
