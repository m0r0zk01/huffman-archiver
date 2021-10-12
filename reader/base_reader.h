#pragma once

#include <string>
#include <vector>

class BaseReader {
public:
    virtual ~BaseReader() = default;

    virtual bool ReachedEOF() = 0;
    virtual bool ReadNextBit() = 0;
    virtual int64_t ReadBitsToInt(size_t amount) = 0;
    virtual std::vector<bool> ReadBits(size_t amount) = 0;
    virtual std::string GetFilename() const = 0;
    virtual void Reopen() = 0;
};