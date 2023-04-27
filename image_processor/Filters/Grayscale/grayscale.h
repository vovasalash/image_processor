#pragma once

#include "../filter.h"

const double GRAYSCALE_RED = 0.299;
const double GRAYSCALE_GREEN = 0.587;
const double GRAYSCALE_BLUE = 0.114;

class Grayscale : public Filter {
public:
    Image Apply(const Image& image) const override;
};