#include "grayscale.h"

Image Grayscale::Apply(const Image &image) const {
    Image result = image;
    for (size_t i = 0; i < image.GetImage().size(); ++i) {
        for (size_t j = 0; j < image.GetImage()[0].size(); ++j) {
            uint8_t color = static_cast<uint8_t>(GRAYSCALE_BLUE * static_cast<double>(image.GetImage()[i][j].red_) +
                                                 GRAYSCALE_GREEN * static_cast<double>(image.GetImage()[i][j].green_) +
                                                 GRAYSCALE_RED * static_cast<double>(image.GetImage()[i][j].blue_));
            result.SetColor(i, j, {color, color, color});
        }
    }
    return result;
}