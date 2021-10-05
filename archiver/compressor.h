#pragma once

#include "../reader/reader.h"
#include "../writer/writer.h"
#include "../trie/trie.h"

#include <iostream>
#include <string>
#include <unordered_map>

const int FILENAME_END = 256;
const int ONE_MORE_FILE = 257;
const int ARCHIVE_END = 258;

class Archiver {
public:

protected:
    Reader reader_;
    Writer writer_;
};

class Compressor : Archiver {
public:
    Compressor();
    Compressor(std::ostream& os);
    Compressor(std::string_view filename);

    void AddFile(std::string_view filename);
    void EndArchive();

private:
    size_t files_added_;

    using CodeTable = std::unordered_map<size_t, std::pair<size_t, size_t>>;
    CodeTable code_table_;

    void EncodeFileName();
    void MakeCanonicalHuffmanCode(std::vector<std::pair<size_t, size_t>>& codes,
                                  std::unordered_map<size_t, size_t>& cnt_len_code);
    void WriteCodeTableToFile(size_t max_symbol_code_size, std::unordered_map<size_t, size_t>& cnt_len_code);
};

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
