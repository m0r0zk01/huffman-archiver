#pragma once

#include "archiver.h"

class Decompressor : public Archiver {
public:
    Decompressor();
    Decompressor(std::istream& is);
    Decompressor(std::string_view filename);

    void Decompress();

private:
    bool DecompressNextFile();
    void RetrieveTrie(std::vector<size_t>& values,
                      std::unordered_map<size_t, size_t>& cnt_len_code);
    void CountCodeLens(size_t symbols_count, std::unordered_map<size_t, size_t>& cnt_len_code);
    size_t GetNextSymbol();
    std::string RetrieveFilename();

    Trie trie_;
};