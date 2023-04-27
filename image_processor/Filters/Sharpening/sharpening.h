#pragma once

#include "../filter.h"

class Sharpening : public Filter {
public:
    Image Apply(const Image &image) const override;
};