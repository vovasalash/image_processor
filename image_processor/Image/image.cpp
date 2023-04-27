#include "image.h"

Image::Image(size_t height, size_t width) {
    height_ = height;
    width_ = width;
    for (size_t i = 0; i < height; ++i) {
        std::vector<Color> temp(width);
        for (size_t j = 0; j < width; ++j) {
            temp.push_back({0, 0, 0});
        }
        image_.push_back(temp);
    }
}

Image::Image(const std::vector<std::vector<Color>> &color_data) {
    image_ = color_data;
    height_ = color_data.size();
    width_ = color_data[0].size();
}

Image::Image(const Image &image) {
    height_ = image.height_;
    width_ = image.width_;
    image_ = image.image_;
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

const std::vector<std::vector<Color>> &Image::GetImage() const {
    return image_;
}

const Color &Image::GetColor(size_t height, size_t width) const {
    return image_[height][width];
}

void Image::SetColor(size_t height, size_t width, Color color) {
    image_[height][width] = color;
}