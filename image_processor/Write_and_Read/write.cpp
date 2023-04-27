#include "write.h"

void write_and_read::Writer::BMPWrite(unsigned char* bmp_header, size_t size_of_img) {
    bmp_header[magic::BMP_FORMAT_OFFSET_FIRST] = magic::BMP_FORMAT[magic::BMP_FORMAT_OFFSET_FIRST];
    bmp_header[magic::BMP_FORMAT_OFFSET_SECOND] = magic::BMP_FORMAT[magic::BMP_FORMAT_OFFSET_SECOND];
    NumToBytes(size_of_img, bmp_header + magic::BMP_SIZE_OFFSET);
    bmp_header[magic::BMP_POSITION_OFFSET] = magic::BMP_HEADER_SIZE + magic::DIB_HEADER_SIZE;
}

void write_and_read::Writer::DIBWrite(unsigned char* dib_header, size_t width, size_t height) {
    dib_header[magic::DIB_SIZE_OFFSET] = magic::DIB_HEADER_SIZE;
    NumToBytes(width, dib_header + magic::WIDTH_OFFSET);
    NumToBytes(height, dib_header + magic::HEIGHT_OFFSET);
    dib_header[magic::BITS_PER_PIX_OFFSET] = magic::COUNT_OF_BITS_PER_PIX;
    dib_header[magic::NOT_EMPTY_POSITION] = magic::NOT_EMPTY;
}

void write_and_read::Writer::NumToBytes(const size_t numb, unsigned char* chars) {
    *chars = numb;
    for (size_t i = 0; i < magic::BYTES_TO_NUM_OFFSETS.size(); ++i) {
        *(chars + i + 1) = numb >> magic::BYTES_TO_NUM_OFFSETS[i];
    }
}

write_and_read::Writer::Writer(std::string file) {
    file_ = file;
}

void write_and_read::Writer::WriteImage(const Image& image) {
    std::ofstream file_out;
    file_out.open(file_, std::ios::out | std::ios::binary);
    if (!file_out.is_open()) {
        throw std::invalid_argument("NO OPEN!");
    }
    const size_t file_size = magic::BMP_HEADER_SIZE + magic::DIB_HEADER_SIZE +
                             image.GetHeight() * image.GetWidth() * magic::COUNT_OF_COLORS +
                             GetPaddings(image.GetWidth()) * image.GetHeight();
    unsigned char bmp_header[magic::BMP_HEADER_SIZE] = {0};
    BMPWrite(bmp_header, file_size);
    unsigned char dib_header[magic::DIB_HEADER_SIZE] = {0};
    DIBWrite(dib_header, image.GetWidth(), image.GetHeight());
    file_out.write(reinterpret_cast<char*>(bmp_header), magic::BMP_HEADER_SIZE);
    file_out.write(reinterpret_cast<char*>(dib_header), magic::DIB_HEADER_SIZE);
    unsigned char empty_bytes[magic::COUNT_OF_COLORS] = {0, 0, 0};
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            unsigned char red = static_cast<unsigned char>(image.GetColor(i, j).red_);
            unsigned char green = static_cast<unsigned char>(image.GetColor(i, j).green_);
            unsigned char blue = static_cast<unsigned char>(image.GetColor(i, j).blue_);
            unsigned char pixel[] = {red, green, blue};
            file_out.write(reinterpret_cast<char*>(pixel), magic::COUNT_OF_COLORS);
        }
        file_out.write(reinterpret_cast<char*>(empty_bytes), static_cast<int64_t>(GetPaddings(image.GetWidth())));
    }
    file_out.close();
}