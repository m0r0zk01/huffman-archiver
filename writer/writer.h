#pragma once

#include <istream>
#include <vector>

class Writer {
public:
    Writer();
    Writer(std::ostream& os);

    void WriteBit(bool bit);
    void WriteBits(const std::vector<bool>& bits);
    void End();
    void SetOutputStream(std::ostream& os);

private:
    std::ostream* output_stream_;
    size_t bits_left_;
    unsigned char last_byte_;
};