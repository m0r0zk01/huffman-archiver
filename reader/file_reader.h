#pragma once

#include "base_reader.h"

#include <fstream>
#include <string_view>

class FileReader : virtual public BaseReader {
public:
    FileReader() = delete;
    explicit FileReader(std::string_view filename);

    bool ReachedEOF();
    bool ReadNextBit();
    int64_t ReadBitsToInt(size_t amount);
    std::vector<bool> ReadBits(size_t amount);
    std::string GetFilename() const;
    void Reopen();

private:
    std::ifstream input_file_stream_;
    std::string filename_;
    unsigned char current_byte_ = 0;
    size_t bits_left_ = 0;
};
