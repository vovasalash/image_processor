#include "read.h"

write_and_read::Reader::Reader(const std::string& file) {
    file_ = file;
}

Image write_and_read::Reader::ReadFile() {
    unsigned char bmp_header[magic::BMP_HEADER_SIZE];
    unsigned char dib_header[magic::DIB_HEADER_SIZE];

    std::ifstream image;
    image.open(file_, std::fstream::in | std::fstream::binary);
    if (!image.is_open()) {
        throw std::invalid_argument("NO OPEN!");  // ИНФА О ФАЙЛЕ
    }
    if (errno == EACCES) {
        throw std::invalid_argument("Permission denied!");  // ИНФА О ФАЙЛЕ
    }

    image.read(reinterpret_cast<char*>(bmp_header), magic::BMP_HEADER_SIZE);

    if (bmp_header[0] != magic::BMP_FORMAT[0] || bmp_header[1] != magic::BMP_FORMAT[1]) {
        throw std::invalid_argument(file_ + " is not bmp format!\n");
    }

    try {
        image.read(reinterpret_cast<char*>(dib_header), magic::DIB_HEADER_SIZE);
        uint32_t height = BytesToNum(dib_header + magic::HEIGHT_OFFSET);
        uint32_t width = BytesToNum(dib_header + magic::WIDTH_OFFSET);
        Image data_image(height, width);
        std::vector<std::vector<Color>> color_image(height);
        std::vector<Color> temporary(width);
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                unsigned char pixel[magic::COUNT_OF_COLORS];
                image.read(reinterpret_cast<char*>(pixel), magic::COUNT_OF_COLORS);
                temporary[j].SetColor(static_cast<uint8_t>(pixel[0]), static_cast<uint8_t>(pixel[1]),
                                      static_cast<uint8_t>(pixel[2]));
            }
            color_image[i] = temporary;
            image.ignore(static_cast<int64_t>(GetPaddings(width)));
        }
        data_image = Image(color_image);
        image.close();
        return data_image;
    } catch (std::exception& e) {
        throw "Error in reading: " + static_cast<std::string>(e.what());
    }
}

size_t write_and_read::Reader::BytesToNum(unsigned char* chars) {
    size_t result = *chars;
    for (size_t i = 0; i < magic::BYTES_TO_NUM_OFFSETS.size(); ++i) {
        result += *(chars + i + 1) << magic::BYTES_TO_NUM_OFFSETS[i];
    }
    return result;
}

const size_t write_and_read::GetPaddings(size_t width) {
    return (magic::MAX_PADDINGS -
            (width * (magic::COUNT_OF_BITS_PER_PIX / magic::BITS_IN_BYTE)) % magic::MAX_PADDINGS) %
           magic::MAX_PADDINGS;
}
