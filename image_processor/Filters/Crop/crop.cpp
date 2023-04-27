#include "crop.h"

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}

Image Crop::Apply(const Image &image) const {
    size_t new_width = std::min(image.GetWidth(), width_);
    size_t new_height = std::min(image.GetHeight(), height_);
    std::vector<std::vector<Color>> new_image;
    for (size_t i = 0; i < new_height; ++i) {
        std::vector<Color> temporary;
        for (size_t j = 0; j < new_width; ++j) {
            Color color = {image.GetImage()[i][j].red_, image.GetImage()[i][j].green_, image.GetImage()[i][j].blue_};
            temporary.push_back(color);
        }
        new_image.push_back(temporary);
    }
    return Image(new_image);
}