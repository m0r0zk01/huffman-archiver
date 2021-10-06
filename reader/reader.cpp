#include "../utils/extract_filename.h"
#include "reader.h"

#include <climits>

Reader::Reader(std::istream& is) :
      input_stream_(&is),
      has_stream_ownership_(false) {}

Reader::Reader(std::string_view filename) :
      input_stream_(new std::ifstream(filename.data())),
      has_stream_ownership_(true),
      filename_(ExtractFilenameFromFilepath(filename)) {}

Reader::~Reader() {
    if (has_stream_ownership_) {
        delete input_stream_;
    }
}

bool Reader::ReachedEOF() {
    if (!input_stream_) {
        throw "No input file is open";
    }
    if (bits_left_) {
        return false;
    }
    char tmp;
    if (input_stream_->get(tmp)) {
        bits_left_ = CHAR_BIT;
        current_byte_ = static_cast<unsigned char>(tmp);
        return false;
    }
    return true;
}

bool Reader::GetNextBit() {
    if (!bits_left_ && ReachedEOF()) {
        throw "Reached EOF";
    }

    return (current_byte_ >> --bits_left_) % 2;
}

size_t Reader::GetNBit(size_t amount) {
    size_t result = 0;
    for (size_t i = 0; i < amount; ++i) {
        result <<= 1;
        result += GetNextBit();
    }
    return result;
}

void Reader::SetInputStream(std::istream& is) {
    if (has_stream_ownership_) {
        delete input_stream_;
    }
    input_stream_ = &is;
    has_stream_ownership_ = false;
    filename_.clear();
}

void Reader::SetInputStream(std::string_view filename) {
    if (has_stream_ownership_) {
        delete input_stream_;
    }
    input_stream_ = new std::ifstream(filename.data());
    has_stream_ownership_ = true;
    filename_ = filename;
}

std::string Reader::GetFilename() {
    return filename_;
}

void Reader::Seekg(size_t pos) {
    input_stream_->seekg(pos);
}

void Reader::Clear() {
    input_stream_->clear();
}
