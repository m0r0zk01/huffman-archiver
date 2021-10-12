#pragma once

#include "archiver.h"
#include "../reader/base_reader.h"
#include "../writer/base_writer.h"
#include "../binary_trie/binary_trie.h"

#include <memory>

class Decompressor : public Archiver {
public:
    Decompressor() = delete;
    explicit Decompressor(std::unique_ptr<BaseReader> reader);

    void Decompress();

private:
    bool DecompressNextFile();
    BinaryTrie RetrieveTrie(const std::vector<int16_t>& values,
                            const std::unordered_map<int16_t, int16_t>& cnt_len_code);
    void CountCodeLens(int16_t symbols_count, std::unordered_map<int16_t , int16_t>& cnt_len_code);
    void RetrieveCodeInfo();
    int16_t GetNextSymbol();
    std::string RetrieveFilename();

    BinaryTrie trie_;
    std::unique_ptr<BaseReader> reader_;
    std::unique_ptr<BaseWriter> writer_;
};