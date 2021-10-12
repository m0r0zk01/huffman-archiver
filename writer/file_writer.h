#pragma once

#include "base_writer.h"

#include <climits>
#include <fstream>
#include <string_view>

class FileWriter : virtual public BaseWriter {
public:
    FileWriter() = delete;
    explicit FileWriter(const std::string_view filename);
    ~FileWriter();

    void WriteBit(bool bit);
    void WriteBits(int64_t bits, size_t amount);
    void WriteBits(const std::vector<bool>& bits);
    void End() final;

private:
    std::ofstream output_file_stream_;
    size_t bits_left_ = CHAR_BIT;
    unsigned char last_byte_ = 0;
};