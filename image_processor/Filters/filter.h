#pragma once

#include "../Image/image.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual Image Apply(const Image& image) const = 0;

protected:
    std::vector<int> ApplyMatrix(const std::vector<std::vector<int>>& matrix, const Image& image, size_t x,
                                 size_t y) const;
};
