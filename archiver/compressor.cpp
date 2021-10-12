#include "compressor.h"
#include "../priority_queue/priority_queue.h"
#include "../binary_trie/binary_trie.h"

#include <algorithm>
#include <climits>

Compressor::Compressor(std::unique_ptr<BaseWriter> writer) : writer_(std::move(writer)) {}

void Compressor::EncodeFileName() {
    for (char c : reader_->GetFilename()) {
        int16_t result = 0;
        int32_t pow2 = 1;
        for (size_t i = 0; i < CHAR_BIT; ++i, pow2 <<= 1) {
            result += ((c >> (CHAR_BIT - i - 1)) % 2) * pow2;
        }
        writer_->WriteBits(code_table_[result].GetData());
    }
    writer_->WriteBits(code_table_[FILENAME_END].GetData());
}

void Compressor::MakeCanonicalHuffmanCode(const std::vector<std::pair<size_t, size_t>>& codes,
                                          std::unordered_map<size_t, size_t>& cnt_len_code) {
    code_table_.clear();
    HuffmanCode code;
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
        writer_->WriteBits(cnt_len_code[code_size], 9);
    }
}

BinaryTrie Compressor::BuildTrie(std::unordered_map<size_t, size_t>& cnt_bytes) {
    BinaryTrie trie;
    PriorityQueue<std::pair<size_t, std::shared_ptr<BinaryTrie::Node>>> pq;
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
        int64_t symbol = reader_->ReadBitsToInt(8);
        cnt_bytes[symbol]++;
    }
    for (char c : reader_->GetFilename()) {
        int16_t result = 0;
        int16_t pow2 = 1;
        for (size_t i = 0; i < CHAR_BIT; ++i, pow2 <<= 1) {
            result += ((c >> (CHAR_BIT - i - 1)) % 2) * pow2;
        }
        cnt_bytes[result]++;
    }
    return cnt_bytes;
}

void Compressor::EncodeFileAndWriteToArchive() {
    reader_->Reopen();

    while (!reader_->ReachedEOF()) {
        unsigned char byte = reader_->ReadBitsToInt(8);
        writer_->WriteBits(code_table_[byte].GetData());
    }
}

void Compressor::AddFile(std::unique_ptr<BaseReader> reader) {
    if (files_added_) {
        writer_->WriteBits(code_table_[ONE_MORE_FILE].GetData());
    }

    reader_ = std::move(reader);

    auto cnt_bytes = BuildBytesFrequencyMap();
    size_t symbols_count = cnt_bytes.size();

    BinaryTrie trie = BuildTrie(cnt_bytes);

    auto codes = trie.RetrieveCodeSizes();
    std::sort(codes.begin(), codes.end());
    std::unordered_map<size_t, size_t> cnt_len_code;

    MakeCanonicalHuffmanCode(codes, cnt_len_code);
    writer_->WriteBits(symbols_count, 9);
    for (const auto& [len, value] : codes) {
        writer_->WriteBits(value, 9);
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
