#pragma once

#include "../Image/image.h"
#include "magic_const.h"
#include "read.h"

#include <fstream>
#include <string>

namespace write_and_read {
class Writer {
public:
    explicit Writer(std::string file);
    void WriteImage(const Image& image);

private:
    std::string file_;
    void BMPWrite(unsigned char* bmp_header, size_t size_of_img);
    void DIBWrite(unsigned char* dib_header, size_t width, size_t height);
    void NumToBytes(const size_t numb, unsigned char* chars);
};
}  // namespace write_and_read