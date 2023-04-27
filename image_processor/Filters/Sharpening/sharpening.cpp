#include "sharpening.h"
#include "../../Write_and_Read/magic_const.h"

Image Sharpening::Apply(const Image& image) const {
    Image result = image;
    std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, magic::SHARP, -1}, {0, -1, 0}};
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            std::vector<int> pixel_colors = ApplyMatrix(matrix, image, i, j);
            result.SetColor(i, j,
                            {static_cast<uint8_t>(pixel_colors[0]), static_cast<uint8_t>(pixel_colors[1]),
                             static_cast<uint8_t>(pixel_colors[2])});
        }
    }
    return result;
}
