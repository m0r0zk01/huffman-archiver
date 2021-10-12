#pragma once

#include <vector>
#include <unordered_map>

class Archiver {
protected:
    struct HuffmanCode {
        std::vector<bool> code = {0};

        HuffmanCode() = default;
        HuffmanCode(std::vector<bool>& bits);

        void AddZeroes(size_t amount);
        void Increment();

        size_t Size() const;

        std::vector<bool> GetData() const;
    };

    const uint16_t FILENAME_END = 256;
    const uint16_t ONE_MORE_FILE = 257;
    const uint16_t ARCHIVE_END = 258;
};
