#include "../utils/exception.h"
#include "../utils/extract_filename.h"
#include "file_reader.h"

#include <algorithm>
#include <climits>

FileReader::FileReader(std::string_view filename) :
    input_file_stream_(filename.data(), std::ios::binary),
    filename_(ExtractFilenameFromFilepath(filename)) {}

bool FileReader::ReachedEOF() {
    if (input_file_stream_.peek() == EOF) {
        if (input_file_stream_.eof()) {
            return true;
        }
        throw Exception("Error while reading file");
    }
    return false;
}

bool FileReader::ReadNextBit() {
    if (!bits_left_ && ReachedEOF()) {
        throw Exception("Reached EOF");
    } else if (!bits_left_) {
        current_byte_ = input_file_stream_.get();
        bits_left_ = CHAR_BIT;
    }
    return (current_byte_ >> --bits_left_) % 2;
}

int64_t FileReader::ReadBitsToInt(size_t amount) {
    int64_t result = 0;
    int64_t pow2 = 1;
    for (size_t i = 0; i < amount; ++i, pow2 <<= 1) {
        result += ReadNextBit() * pow2;
    }
    return result;
}

std::vector<bool> FileReader::ReadBits(size_t amount) {
    std::vector<bool> result;
    for (size_t i = 0; i < amount; ++i) {
        result.push_back(ReadNextBit());
    }
    return result;
}

std::string FileReader::GetFilename() const {
    return filename_;
}

void FileReader::Reopen() {
    input_file_stream_.clear();
    input_file_stream_.seekg(0);
}