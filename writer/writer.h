#pragma once

#include <istream>
#include <vector>

class Writer {
public:
    Writer(std::ostream& ios);

    void WriteBit(bool bit);
    void WriteBits(const std::vector<bool>& bits);
    void End();

private:
    std::ostream& output_stream_;
    size_t bits_left_;
    unsigned char last_byte_;
};