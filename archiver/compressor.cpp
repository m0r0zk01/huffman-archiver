#include "compressor.h"
#include "../priority_queue/priority_queue.h"

#include <algorithm>
#include <bitset>
#include <iostream>

Compressor::Compressor(Writer* writer) : Archiver(nullptr, writer) {}

void Compressor::EncodeFileName() {
    for (char c : reader_->GetFilename()) {
        writer_->WriteBits(code_table_[c].GetData());
    }
    writer_->WriteBits(code_table_[FILENAME_END].GetData());
}

void Compressor::MakeCanonicalHuffmanCode(const std::vector<std::pair<size_t, size_t>>& codes,
                                          std::unordered_map<size_t, size_t>& cnt_len_code) {
    code_table_.clear();
    Code code;
    for (const auto& [len, value] : codes) {
        code.AddZeroes(len - code.Size());
        cnt_len_code[len]++;
        code_table_[value] = code;
        code.Increment();
    }
}

void Compressor::WriteCodeTableToFile(size_t max_symbol_code_size,
                                      std::unordered_map<size_t, size_t>& cnt_len_code) {
    for (size_t code_size = 1; code_size <= max_symbol_code_size; ++code_size) {
        writer_->WriteNBits(cnt_len_code[code_size], 9);
    }
}

Trie Compressor::BuildTrie(std::unordered_map<size_t, size_t>& cnt_bytes) {
    Trie trie;
    PriorityQueue<std::pair<size_t, std::shared_ptr<Trie::Node>>> pq;
    for (const auto& [byte, cnt] : cnt_bytes) {
        pq.Insert({cnt, trie.CreateNode(byte, true)});
    }
    while (pq.Size() > 1) {
        auto v1 = pq.PopFront(), v2 = pq.PopFront();
        pq.Insert({v1.first + v2.first, trie.CreateNode(0, false, v1.second, v2.second)});
    }
    trie.SetRoot(pq.PopFront().second);

    return trie;
}

std::unordered_map<size_t, size_t> Compressor::BuildBytesFrequencyMap() {
    std::unordered_map<size_t, size_t> cnt_bytes{{FILENAME_END, 1}, {ONE_MORE_FILE, 1}, {ARCHIVE_END, 1}};
    while (!reader_->ReachedEOF()) {
        unsigned char byte = reader_->GetNBit(8);
        cnt_bytes[byte]++;
    }
    for (char c : reader_->GetFilename()) {
        cnt_bytes[c]++;
    }
    return cnt_bytes;
}

void Compressor::EncodeFileAndWriteToArchive() {
    reader_->Clear();
    reader_->Seekg(0);

    while (!reader_->ReachedEOF()) {
        unsigned char byte = reader_->GetNBit(8);
        writer_->WriteBits(code_table_[byte].GetData());
    }
}

void Compressor::AddFile(Reader* reader) {
    if (files_added_) {
        writer_->WriteBits(code_table_[ONE_MORE_FILE].GetData());
    }

    ChangeReader(reader);

    auto cnt_bytes = BuildBytesFrequencyMap();
    size_t symbols_count = cnt_bytes.size();

    Trie trie = BuildTrie(cnt_bytes);

    auto codes = trie.RetrieveCodeSizes();
    std::sort(codes.begin(), codes.end());
    std::unordered_map<size_t, size_t> cnt_len_code;

    MakeCanonicalHuffmanCode(codes, cnt_len_code);
    writer_->WriteNBits(symbols_count, 9);
    for (const auto& [len, value] : codes) {
        writer_->WriteNBits(value, 9);
    }
    WriteCodeTableToFile(codes.back().first, cnt_len_code);
    EncodeFileName();

    EncodeFileAndWriteToArchive();

    files_added_++;
}

void Compressor::EndArchive() {
    writer_->WriteBits(code_table_[ARCHIVE_END].GetData());
    writer_->End();
}
