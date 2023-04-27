#include "negative.h"
#include "../../Write_and_Read/magic_const.h"

Image Negative::Apply(const Image &image) const {
    Image result = image;
    for (size_t i = 0; i < image.GetImage().size(); ++i) {
        for (size_t j = 0; j < image.GetImage()[0].size(); ++j) {
            uint8_t red = magic::WHITE - image.GetImage()[i][j].red_;
            uint8_t green = magic::WHITE - image.GetImage()[i][j].green_;
            uint8_t blue = magic::WHITE - image.GetImage()[i][j].blue_;
            result.SetColor(i, j, {red, green, blue});
        }
    }
    return result;
}
