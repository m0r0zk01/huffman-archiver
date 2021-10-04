#pragma once

#include <fstream>
#include <istream>
#include <vector>

class Writer {
public:
    Writer();
    Writer(std::ostream& os);
    Writer(std::string_view filename);

    ~Writer();

    void WriteBit(bool bit);
    void WriteBits(const std::vector<bool>& bits);
    void WriteNBits(size_t bits, size_t amount);
    void End();
    void SetOutputStream(std::ostream& os);

private:
    std::ostream* output_stream_;
    bool has_stream_ownership_;
    size_t bits_left_;
    unsigned char last_byte_;
};