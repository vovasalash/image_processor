#pragma once

#include "../Image/image.h"
#include "magic_const.h"

#include <cerrno>
#include <fstream>
#include <string>

namespace write_and_read {

class Reader {
public:
    explicit Reader(const std::string& file);
    Image ReadFile();

private:
    std::string file_;
    size_t BytesToNum(unsigned char* chars);
};

const size_t GetPaddings(size_t width);
}  // namespace write_and_read
