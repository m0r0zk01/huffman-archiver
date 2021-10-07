#pragma once

#include "../reader/reader.h"
#include "../writer/writer.h"
#include "../trie/trie.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Archiver {
protected:
    struct Code {
        std::vector<bool> code = {0};

        Code() = default;
        Code(std::vector<bool>& bits);

        void AddBit(bool bit);
        void AddZeroes(size_t amount);
        void Increment();

        size_t Size() const;

        std::vector<bool> GetData() const;
    };

    Archiver(Reader* reader, Writer* writer);
    ~Archiver();

    void ChangeReader(Reader* reader);
    void ChangeWriter(Writer* writer);

    const uint FILENAME_END = 256;
    const uint ONE_MORE_FILE = 257;
    const uint ARCHIVE_END = 258;

    Reader* reader_ = nullptr;
    bool is_reader_dynamically_allocated = true;
    Writer* writer_ = nullptr;
    bool is_writer_dynamically_allocated = true;
};
