#include "writer.h"

#include <climits>
#include <iostream>

Writer::Writer(std::ostream& ios) : output_stream_(ios), bits_left_(CHAR_BIT), last_byte_(0) {}

void Writer::WriteBit(bool bit) {
    if (!bits_left_) {
        output_stream_ << last_byte_;
        last_byte_ = 0;
        bits_left_ = CHAR_BIT;
    }

    last_byte_ |= bit * (1 << --bits_left_);
}

void Writer::WriteBits(const std::vector<bool>& bits) {
    for (bool bit : bits) {
        WriteBit(bit);
    }
}

void Writer::Close() {
    if (bits_left_ != CHAR_BIT) {
        output_stream_ << last_byte_;
    }
}