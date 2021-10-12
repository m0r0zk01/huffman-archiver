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
    BinaryTrie RetrieveTrie(const std::vector<uint16_t>& values,
                            const std::unordered_map<uint16_t, uint16_t>& cnt_len_code);
    void CountCodeLens(uint16_t symbols_count, std::unordered_map<uint16_t , uint16_t>& cnt_len_code);
    void RetrieveCodeInfo();
    uint16_t GetNextSymbol();
    std::string RetrieveFilename();

    BinaryTrie trie_;
    std::unique_ptr<BaseReader> reader_;
    std::unique_ptr<BaseWriter> writer_;
};