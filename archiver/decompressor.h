#pragma once

#include "archiver.h"
#include <iostream>
class Decompressor : public Archiver {
public:
    Decompressor() = delete;

    explicit Decompressor(Reader* reader);

    void Decompress();

private:
    bool DecompressNextFile();
    Trie RetrieveTrie(const std::vector<size_t>& values,
                      const std::unordered_map<size_t, size_t>& cnt_len_code);
    void CountCodeLens(size_t symbols_count, std::unordered_map<size_t, size_t>& cnt_len_code);
    size_t GetNextSymbol();
    std::string RetrieveFilename();

    Trie trie_;
};