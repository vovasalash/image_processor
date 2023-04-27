#pragma once

#include "color.h"

#include <cstddef>
#include <vector>

class Image {
public:
    Image() = default;
    Image(size_t height, size_t width);
    explicit Image(const std::vector<std::vector<Color>>& color_data);
    Image(const Image& image);
    ~Image() = default;

    size_t GetHeight() const;
    size_t GetWidth() const;
    const std::vector<std::vector<Color>>& GetImage() const;
    const Color& GetColor(size_t height, size_t width) const;
    void SetColor(size_t height, size_t width, Color color);

private:
    size_t height_ = 0;
    size_t width_ = 0;
    std::vector<std::vector<Color>> image_;
};