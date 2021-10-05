#pragma once

#include "archiver.h"

class Compressor : Archiver {
public:
    Compressor() = delete;
    explicit Compressor(std::ostream& os);
    explicit Compressor(std::string_view filename);

    void AddFile(const std::string_view filename);
    void EndArchive();

private:
    size_t files_added_ = 0;

    using CodeTable = std::unordered_map<size_t, std::pair<size_t, size_t>>;
    CodeTable code_table_;

    void EncodeFileName();
    void MakeCanonicalHuffmanCode(const std::vector<std::pair<size_t, size_t>>& codes,
                                  std::unordered_map<size_t, size_t>& cnt_len_code);
    void WriteCodeTableToFile(size_t max_symbol_code_size,
                              const std::unordered_map<size_t, size_t>& cnt_len_code);
};