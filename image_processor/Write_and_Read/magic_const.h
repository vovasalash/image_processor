#pragma once

#include <vector>

namespace magic {
const int BITS_PER_PIX_OFFSET = 14;

const int BMP_HEADER_SIZE = 14;
const int BMP_SIZE_OFFSET = 2;
const int BMP_POSITION_OFFSET = 10;
const int BMP_FORMAT_OFFSET_FIRST = 0;
const int BMP_FORMAT_OFFSET_SECOND = 1;

const int DIB_HEADER_SIZE = 40;
const int DIB_SIZE_OFFSET = 0;
const int BITS_IN_BYTE = 8;
const int WIDTH_OFFSET = 4;
const int HEIGHT_OFFSET = 8;

const int MAX_PADDINGS = 4;

const int COUNT_OF_COLORS = 3;
const int COUNT_OF_BITS_PER_PIX = 24;

const int NOT_EMPTY = 1;
const int NOT_EMPTY_POSITION = 12;

const std::vector<char> BMP_FORMAT = {'B', 'M'};
const std::vector<int> BYTES_TO_NUM_OFFSETS = {8, 16, 24};

const int WHITE = 255;
const int BLACK = 0;

const int SHARP = 5;

}  // namespace magic