#include "Color.h"

RGBColor::RGBColor(unsigned char red, unsigned char green, unsigned char blue) {
    rgbColor.rgbRed = red;
    rgbColor.rgbGreen = green;
    rgbColor.rgbBlue = blue;
    rgbColor.rgbReserved = 0;
}

RGBColor::RGBColor() {
    rgbColor.rgbBlue = 0;
    rgbColor.rgbGreen = 0;
    rgbColor.rgbRed = 0;
    rgbColor.rgbReserved = 0;
}

unsigned char RGBColor::r() const { return rgbColor.rgbRed; }
unsigned char RGBColor::g() const { return rgbColor.rgbGreen; }
unsigned char RGBColor::b() const { return rgbColor.rgbBlue; }

bool RGBColor::operator==(const RGBColor& other) const {
    return rgbColor.rgbRed == other.rgbColor.rgbRed
        && rgbColor.rgbGreen == other.rgbColor.rgbGreen
        && rgbColor.rgbBlue == other.rgbColor.rgbBlue;
}

bool RGBColor::operator!=(const RGBColor& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const RGBColor& color) {
    os << "R: " << static_cast<int>(color.rgbColor.rgbRed) << " "
        << "G: " << static_cast<int>(color.rgbColor.rgbGreen) << " "
        << "B: " << static_cast<int>(color.rgbColor.rgbBlue);
    return os;
}
