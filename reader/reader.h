#pragma once

#include <fstream>
#include <istream>
#include <memory>
#include <string_view>
#include <vector>

class Reader {
public:
    Reader() = default;
    explicit Reader(std::istream& is);
    explicit Reader(std::string_view filename);

    ~Reader();

    bool ReachedEOF();
    bool GetNextBit();
    size_t GetNBit(size_t amount);
    std::vector<bool> GetNBitAsVector(size_t amount);

    void SetInputStream(std::istream& is);
    void SetInputStream(std::string_view filename);

    std::string GetFilename();

    void Seekg(size_t pos);
    void Clear();

private:
    std::istream* input_stream_ = nullptr;
    unsigned char current_byte_ = 0;
    bool has_stream_ownership_ = false;
    std::string filename_;
    size_t bits_left_ = 0;
};
