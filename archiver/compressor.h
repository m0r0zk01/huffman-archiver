#pragma once

#include "archiver.h"

class Compressor : Archiver {
public:
    Compressor() = delete;
    explicit Compressor(Writer* writer);

    void AddFile(Reader* reader);
    void EndArchive();

private:
    void EncodeFileName();
    void MakeCanonicalHuffmanCode(const std::vector<std::pair<size_t, size_t>>& codes,
                                  std::unordered_map<size_t, size_t>& cnt_len_code);
    void WriteCodeTableToFile(size_t max_symbol_code_size,
                              std::unordered_map<size_t, size_t>& cnt_len_code);
    Trie BuildTrie(std::unordered_map<size_t, size_t>& cnt_bytes);
    std::unordered_map<size_t, size_t> BuildBytesFrequencyMap();
    void EncodeFileAndWriteToArchive();

    size_t files_added_ = 0;

    using CodeTable = std::unordered_map<size_t, std::pair<size_t, size_t>>;
    CodeTable code_table_;
};