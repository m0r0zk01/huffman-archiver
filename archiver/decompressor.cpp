#include "decompressor.h"
#include "../utils/exception.h"
#include "../writer/file_writer.h"

#include <unordered_map>

Decompressor::Decompressor(std::unique_ptr<BaseReader> reader) : reader_(std::move(reader)) {}

BinaryTrie Decompressor::RetrieveTrie(const std::vector<uint16_t>& values,
                                      const std::unordered_map<uint16_t, uint16_t>& cnt_len_code) {
    BinaryTrie trie;
    trie.SetRoot(std::make_shared<BinaryTrie::Node>());
    HuffmanCode code;
    uint16_t codes_with_current_len_left = cnt_len_code.at(1);
    uint16_t codes_retrieved = 0;
    while (codes_retrieved != values.size()) {
        while (!codes_with_current_len_left) {
            code.AddZeroes(1);
            codes_with_current_len_left = cnt_len_code.at(code.Size());
        }
        trie.AddCode(values[codes_retrieved], code.GetData(), code.Size());
        codes_with_current_len_left--;
        codes_retrieved++;
        code.Increment();
    }
    return trie;
}

void Decompressor::CountCodeLens(uint16_t symbols_count, std::unordered_map<uint16_t, uint16_t>& cnt_len_code) {
    uint16_t codes_read = 0;
    uint16_t code_len = 1;
    while (codes_read != symbols_count) {
        uint16_t v = reader_->ReadBitsToInt(9);
        cnt_len_code[code_len++] = v;
        codes_read += v;
    }
}

uint16_t Decompressor::GetNextSymbol() {
    BinaryTrie::NodePtr node = trie_.GetRoot();
    while (!node->is_leaf) {
        bool bit = reader_->ReadNextBit();
        node = bit ? node->_1 : node->_0;
        if (!node) {
            throw Exception("Corrupted archive!");
        }
    }
    return node->value;
}

std::string Decompressor::RetrieveFilename() {
    std::string filename;
    uint16_t symbol = GetNextSymbol();
    while (symbol != FILENAME_END) {
        uint16_t result = 0;
        int32_t pow2 = 1;
        for (size_t i = 0; i < CHAR_BIT; ++i, pow2 <<= 1) {
            result += ((symbol >> (CHAR_BIT - i - 1)) % 2) * pow2;
        }
        filename.push_back(result);
        symbol = GetNextSymbol();
    }
    return filename;
}

void Decompressor::RetrieveCodeInfo() {
    uint16_t symbols_count = reader_->ReadBitsToInt(9);
    std::vector<uint16_t> values;
    for (uint16_t i = 0; i < symbols_count; ++i) {
        values.push_back(reader_->ReadBitsToInt(9));
    }

    std::unordered_map<uint16_t, uint16_t> cnt_len_code;
    CountCodeLens(symbols_count, cnt_len_code);

    trie_ = RetrieveTrie(values, cnt_len_code);
}

bool Decompressor::DecompressNextFile() {
    RetrieveCodeInfo();
    std::string filename = RetrieveFilename();
    writer_.reset(new FileWriter(filename));
    uint16_t symbol = GetNextSymbol();
    while (symbol != ONE_MORE_FILE && symbol != ARCHIVE_END) {
        writer_->WriteBits(symbol, 8);
        symbol = GetNextSymbol();
    }
    writer_->End();
    return symbol == ONE_MORE_FILE;
}

void Decompressor::Decompress() {
    while (DecompressNextFile()) {}
}