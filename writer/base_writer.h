#pragma once

#include <cstdint>
#include <vector>

class BaseWriter {
public:
    virtual ~BaseWriter() = default;

    virtual void WriteBit(bool bit) = 0;
    virtual void WriteBits(int64_t bits, size_t amount) = 0;
    virtual void WriteBits(const std::vector<bool>& bits) = 0;
    virtual void End() = 0;
};