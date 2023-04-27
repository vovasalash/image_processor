#pragma once

#include "../filter.h"

const uint8_t WHITE = 255;
const uint8_t BLACK = 0;

class EdgeDetection : public Filter {
public:
    explicit EdgeDetection(double threshold);
    Image Apply(const Image& image) const override;

private:
    double threshold_;
};
