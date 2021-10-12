#pragma once

#include "archiver.h"
#include "../reader/base_reader.h"
#include "../writer/base_writer.h"
#include "../binary_trie/binary_trie.h"

#include <memory>

class Compressor : Archiver {
public:
    Compressor() = delete;
    explicit Compressor(std::unique_ptr<BaseWriter> writer);

    void AddFile(std::unique_ptr<BaseReader> reader);
    void EndArchive();

private:
    void EncodeFileName();
    void MakeCanonicalHuffmanCode(const std::vector<std::pair<size_t, size_t>>& codes,
                                  std::unordered_map<size_t, size_t>& cnt_len_code);
    void WriteCodeTableToFile(size_t max_symbol_code_size,
                              std::unordered_map<size_t, size_t>& cnt_len_code);
    BinaryTrie BuildTrie(std::unordered_map<size_t, size_t>& cnt_bytes);
    std::unordered_map<size_t, size_t> BuildBytesFrequencyMap();
    void EncodeFileAndWriteToArchive();

    using CodeTable = std::unordered_map<size_t, HuffmanCode>;
    CodeTable code_table_;

    size_t files_added_ = 0;
    std::unique_ptr<BaseWriter> writer_ = nullptr;
    std::unique_ptr<BaseReader> reader_ = nullptr;
};