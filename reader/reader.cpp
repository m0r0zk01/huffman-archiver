#include <climits>
#include <iostream>

#include "reader.h"

Reader::Reader(std::istream& is) : current_byte_(0), input_stream_(is), bits_left_(0) {}

bool Reader::ReachedEOF() {
    if (bits_left_) {
        return false;
    } else if (input_stream_ >> current_byte_) {
        bits_left_ = CHAR_BIT;
        return false;
    }
    return true;
}

bool Reader::GetNextBit() {
    if (!bits_left_ && ReachedEOF()) {
        throw "Reached EOF";
    }

    return (current_byte_ >> --bits_left_) % 2;
}