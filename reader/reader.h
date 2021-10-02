#pragma once

#include <istream>

class Reader {
public:
    Reader(std::istream& is);

    bool ReachedEOF();
    bool GetNextBit();

private:
    unsigned char current_byte_;

    std::istream& input_stream_;
    size_t bits_left_;
};
