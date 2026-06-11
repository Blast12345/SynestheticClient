#pragma once

#include <cstdint>

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    Color(const uint8_t red, const uint8_t green, const uint8_t blue)
        : red(red), green(green), blue(blue) {}
};
