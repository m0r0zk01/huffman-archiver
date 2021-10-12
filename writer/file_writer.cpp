#include "file_writer.h"

#include <iostream>

FileWriter::FileWriter(const std::string_view filename) : output_file_stream_(filename.data(), std::ios::binary) {}

FileWriter::~FileWriter() {
    End();
}

void FileWriter::WriteBit(bool bit) {
    if (!bits_left_) {
        output_file_stream_.put(last_byte_);
        last_byte_ = 0;
        bits_left_ = CHAR_BIT;
    }

    last_byte_ |= bit * (1 << --bits_left_);
}

void FileWriter::WriteBits(const std::vector<bool>& bits) {
    for (bool bit : bits) {
        WriteBit(bit);
    }
}

void FileWriter::WriteBits(int64_t bits, size_t amount) {
    for (size_t i = 0; i < amount; ++i) {
        WriteBit(bits % 2);
        bits >>= 1;
    }
}

void FileWriter::End() {
    if (bits_left_ != CHAR_BIT) {
        output_file_stream_.put(last_byte_);
        bits_left_ = CHAR_BIT;
    }
}
