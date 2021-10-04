#pragma once

#include <fstream>
#include <istream>
#include <memory>
#include <string_view>

class Reader {
public:
    Reader();
    Reader(std::istream& is);
    Reader(std::string_view filename);

    ~Reader();

    bool ReachedEOF();
    bool GetNextBit();
    size_t GetNBit(size_t num);

    void SetInputStream(std::istream& is);
    void SetInputStream(std::string_view filename);

    std::string GetFilename();

    void Seekg(size_t pos);
    void Clear();


private:
    unsigned char current_byte_;

    std::istream* input_stream_;
    bool has_stream_ownership_;
    std::string filename_;
    size_t bits_left_;
};
