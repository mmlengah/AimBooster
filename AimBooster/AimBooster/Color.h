#pragma once
#include <iostream>

// Custom struct to hold a color in BGR format
struct Color {
    // BGR components
    unsigned char b, g, r;

    // Constructor to initialize a color
    Color(unsigned char blue, unsigned char green, unsigned char red)
        : b(blue), g(green), r(red) {}

    bool operator==(const Color& other) const {
        return b == other.b && g == other.g && r == other.r;
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }

    // Friend function to override the ostream operator
    // This allows us to print Color objects in RGB format
    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "R: " << static_cast<int>(color.r) << " "
            << "G: " << static_cast<int>(color.g) << " "
            << "B: " << static_cast<int>(color.b);
        return os;
    }
};