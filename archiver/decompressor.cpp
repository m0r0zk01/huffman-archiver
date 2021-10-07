#include "decompressor.h"
#include "../utils/exception.h"

#include <unordered_map>

Decompressor::Decompressor(Reader* reader) : Archiver(reader, nullptr) {}

Trie Decompressor::RetrieveTrie(const std::vector<size_t>& values,
                                const std::unordered_map<size_t, size_t>& cnt_len_code) {
    Trie trie;
    trie.SetRoot(std::make_shared<Trie::Node>());
    Code code;
    size_t codes_with_current_len_left = cnt_len_code.at(1);
    size_t codes_retrieved = 0;
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

void Decompressor::CountCodeLens(size_t symbols_count, std::unordered_map<size_t, size_t>& cnt_len_code) {
    size_t codes_read = 0;
    size_t code_len = 1;
    while (codes_read != symbols_count) {
        size_t v = reader_->GetNBit(9);
        cnt_len_code[code_len++] = v;
        codes_read += v;
    }
}

size_t Decompressor::GetNextSymbol() {
    Trie::NodePtr node = trie_.GetRoot();
    while (!node->is_leaf) {
        bool bit = reader_->GetNextBit();
        node = bit ? node->_1 : node->_0;
        if (!node) {
            throw Exception("Corrupted archive!");
        }
    }
    return node->value;
}

std::string Decompressor::RetrieveFilename() {
    std::string result;
    size_t symbol = GetNextSymbol();
    while (symbol != FILENAME_END) {
        result.push_back(symbol);
        symbol = GetNextSymbol();
    }
    return result;
}

void Decompressor::RetrieveCodeInfo() {
    size_t symbols_count = reader_->GetNBit(9);
    std::vector<size_t> values;
    for (size_t i = 0; i < symbols_count; ++i) {
        values.push_back(reader_->GetNBit(9));
    }

    std::unordered_map<size_t, size_t> cnt_len_code;
    CountCodeLens(symbols_count, cnt_len_code);

    trie_ = RetrieveTrie(values, cnt_len_code);
}

bool Decompressor::DecompressNextFile() {
    RetrieveCodeInfo();
    std::string filename = RetrieveFilename();
    writer_->SetOutputStream(filename);
    size_t symbol = GetNextSymbol();
    while (symbol != ONE_MORE_FILE && symbol != ARCHIVE_END) {
        writer_->WriteNBits(symbol, 8);
        symbol = GetNextSymbol();
    }
    writer_->End();
    return symbol == ONE_MORE_FILE;
}

void Decompressor::Decompress() {
    while (DecompressNextFile()) {}
}