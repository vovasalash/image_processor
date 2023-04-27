#pragma once

#include <cstdint>

struct Color {
    uint8_t red_ = 0;
    uint8_t green_ = 0;
    uint8_t blue_ = 0;
    Color() = default;
    Color(uint8_t red, uint8_t green, uint8_t blue);
    void SetColor(uint8_t red, uint8_t green, uint8_t blue);
};