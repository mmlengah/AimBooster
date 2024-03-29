#pragma once
#include <iostream>

struct Color {
    unsigned char b, g, r;

    Color(unsigned char blue, unsigned char green, unsigned char red)
        : b(blue), g(green), r(red) {}

    Color()
        : b(0), g(0), r(0) {}

    bool operator==(const Color& other) const {
        return b == other.b && g == other.g && r == other.r;
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "R: " << static_cast<int>(color.r) << " "
            << "G: " << static_cast<int>(color.g) << " "
            << "B: " << static_cast<int>(color.b);
        return os;
    }
};