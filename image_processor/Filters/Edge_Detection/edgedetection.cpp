#include "edgedetection.h"
#include "../Grayscale/grayscale.h"

EdgeDetection::EdgeDetection(double threshold) {
    threshold_ = threshold;
}

Image EdgeDetection::Apply(const Image &image) const {
    std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    Image grayscale_image = Grayscale().Apply(image);
    Image result = grayscale_image;
    for (size_t i = 0; i < grayscale_image.GetHeight(); ++i) {
        for (size_t j = 0; j < grayscale_image.GetWidth(); ++j) {
            std::vector<int> pixel_colors = ApplyMatrix(matrix, grayscale_image, i, j);
            if (pixel_colors[2] > threshold_ * WHITE) {
                result.SetColor(i, j, {WHITE, WHITE, WHITE});
            } else {
                result.SetColor(i, j, {BLACK, BLACK, BLACK});
            }
        }
    }
    return result;
}