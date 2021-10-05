#include "compressor.h"
#include "../priority_queue/priority_queue.h"

#include <algorithm>
#include <bitset>
#include <climits>
#include <iostream>

Compressor::Compressor(std::ostream& os) {
    writer_.SetOutputStream(os);
}

Compressor::Compressor(std::string_view filename) {
    writer_.SetOutputStream(filename);
}

void Compressor::EncodeFileName() {
    for (char c : reader_.GetFilename()) {
        writer_.WriteNBits(code_table_[c].first, code_table_[c].second);
    }
}

void Compressor::MakeCanonicalHuffmanCode(const std::vector<std::pair<size_t, size_t>>& codes,
                                          std::unordered_map<size_t, size_t>& cnt_len_code) {
    code_table_.clear();
    size_t code = 0;
    size_t prev_len = codes[0].first;
    for (const auto& [len, value] : codes) {
        code <<= (len - prev_len);
        cnt_len_code[len]++;
        code_table_[value] = {code, len};
        prev_len = len;
        code++;
    }
}

void Compressor::WriteCodeTableToFile(size_t max_symbol_code_size,
                                      const std::unordered_map<size_t, size_t>& cnt_len_code) {
    for (size_t code_size = 1; code_size <= max_symbol_code_size; ++code_size) {
        writer_.WriteNBits(cnt_len_code.at(code_size), 9);
    }
}

void Compressor::AddFile(const std::string_view filename) {
    if (files_added_) {
        writer_.WriteNBits(code_table_[ONE_MORE_FILE].first, code_table_[ONE_MORE_FILE].second);
    }

    reader_.SetInputStream(filename);
    std::unordered_map<size_t, size_t> cnt_bytes{{FILENAME_END, 1}, {ONE_MORE_FILE, 1}, {ARCHIVE_END, 1}};
    while (!reader_.ReachedEOF()) {
        unsigned char byte = reader_.GetNBit(8);
        cnt_bytes[byte]++;
    }

    for (char c : filename) {
        cnt_bytes[c]++;
    }

    PriorityQueue<std::pair<size_t, Trie::Node*>> pq;
    Trie trie;
    size_t symbols_count = cnt_bytes.size();
    for (const auto& [byte, cnt] : cnt_bytes) {
        pq.Insert({cnt, trie.InsertNode(byte, true)});
    }
    while (pq.Size() > 1) {
        auto v1 = pq.PopFront(), v2 = pq.PopFront();
        pq.Insert({v1.first + v2.first, trie.InsertNode(0, false, v1.second, v2.second)});
    }
    trie.SetRoot(pq.PopFront().second);

    auto codes = trie.RetrieveCodeSizes();
    std::sort(codes.begin(), codes.end());
    std::unordered_map<size_t, size_t> cnt_len_code;

    MakeCanonicalHuffmanCode(codes, cnt_len_code);
    writer_.WriteNBits(symbols_count, 9);
    for (const auto& [len, value] : codes) {
        writer_.WriteNBits(value, 9);
    }
    WriteCodeTableToFile(codes.back().first, cnt_len_code);
    EncodeFileName();
    writer_.WriteNBits(code_table_[FILENAME_END].first, code_table_[FILENAME_END].second);

    reader_.Clear();
    reader_.Seekg(0);

    while (!reader_.ReachedEOF()) {
        unsigned char byte = reader_.GetNBit(8);
        writer_.WriteNBits(code_table_[byte].first, code_table_[byte].second);
    }

    files_added_++;
}

void Compressor::EndArchive() {
    writer_.WriteNBits(code_table_[ARCHIVE_END].first, code_table_[ARCHIVE_END].second);
    writer_.End();
}
