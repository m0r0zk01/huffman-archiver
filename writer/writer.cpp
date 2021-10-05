#include "writer.h"

#include <iostream>

Writer::Writer(std::ostream& os) :
      output_stream_(&os),
      has_stream_ownership_(false) {}

Writer::Writer(std::string_view filename) :
      output_stream_(new std::ofstream(filename.data())),
      has_stream_ownership_(true) {}

Writer::~Writer() {
    End();
    if (has_stream_ownership_) {
        delete output_stream_;
    }
}

void Writer::WriteBit(bool bit) {
    if (!output_stream_) {
        throw "No output file is open";
    }
    if (!bits_left_) {
        output_stream_->put(last_byte_);
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

void Writer::WriteNBits(size_t bits, size_t amount) {
    for (size_t i = 0; i < amount; ++i) {
        WriteBit((bits >> (amount - i - 1)) % 2);
    }
}

void Writer::End() {
    if (!output_stream_) {
        throw "No output file is open";
    }
    if (bits_left_ != CHAR_BIT) {
        output_stream_->put(last_byte_);
        bits_left_ = CHAR_BIT;
    }
}

void Writer::SetOutputStream(std::ostream& os) {
    if (has_stream_ownership_) {
        delete output_stream_;
    }
    output_stream_ = &os;
    has_stream_ownership_ = false;
}

void Writer::SetOutputStream(std::string_view filename) {
    if (has_stream_ownership_) {
        delete output_stream_;
    }
    output_stream_ = new std::ofstream(filename.data());
    has_stream_ownership_ = true;
}
