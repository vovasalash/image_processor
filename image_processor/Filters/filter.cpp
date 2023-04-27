#include "filter.h"
#include "../Write_and_Read/magic_const.h"

std::vector<int> Filter::ApplyMatrix(const std::vector<std::vector<int>>& matrix, const Image& image, size_t x,
                                     size_t y) const {
    int red = 0;
    int green = 0;
    int blue = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            auto color = image.GetColor(
                std::clamp(static_cast<int>(x) - 1 + static_cast<int>(i), 0, static_cast<int>(image.GetHeight() - 1)),
                std::clamp(static_cast<int>(y) - 1 + static_cast<int>(j), 0, static_cast<int>(image.GetWidth() - 1)));
            red += color.red_ * matrix[i][j];
            green += color.green_ * matrix[i][j];
            blue += color.blue_ * matrix[i][j];
        }
    }
    return {std::min(magic::WHITE, std::max(0, red)), std::min(magic::WHITE, std::max(0, green)),
            std::min(magic::WHITE, std::max(0, blue))};
}
