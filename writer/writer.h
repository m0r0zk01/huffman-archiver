#pragma once

#include <climits>
#include <fstream>
#include <istream>
#include <vector>

class Writer {
public:
    Writer() = default;
    explicit Writer(std::ostream& os);
    explicit Writer(std::string_view filename);

    ~Writer();

    void WriteBit(bool bit);
    void WriteBits(const std::vector<bool>& bits);
    void WriteNBits(size_t bits, size_t amount);
    void End();

    void SetOutputStream(std::ostream& os);
    void SetOutputStream(const std::string& filename);

private:
    std::ostream* output_stream_ = nullptr;
    bool has_stream_ownership_ = false;
    size_t bits_left_ = CHAR_BIT;
    unsigned char last_byte_ = 0;
};