#pragma once

#include <fstream>
#include <istream>
#include <memory>

class Reader {
public:
    Reader();
    Reader(std::istream& is);
    Reader(std::string_view filename);

    ~Reader();

    bool ReachedEOF();
    bool GetNextBit();
    void SetInputStream(std::istream& is);

    size_t GetNBit(size_t num);

private:
    unsigned char current_byte_;

    std::istream* input_stream_;
    bool has_stream_ownership_;
    size_t bits_left_;
};
