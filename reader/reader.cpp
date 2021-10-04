#include "reader.h"

#include <climits>

Reader::Reader() :
      current_byte_(0),
      input_stream_(nullptr),
      has_stream_ownership_(false),
      bits_left_(0) {}


Reader::Reader(std::istream& is) :
      current_byte_(0),
      input_stream_(&is),
      has_stream_ownership_(false),
      bits_left_(0) {}

Reader::Reader(std::string_view filename) :
      current_byte_(0),
      input_stream_(new std::ifstream(filename.data())),
      has_stream_ownership_(true),
      filename_(filename),
      bits_left_(0) {}

Reader::~Reader() {
    if (has_stream_ownership_) {
        delete input_stream_;
    }
}

bool Reader::ReachedEOF() {
    if (bits_left_) {
        return false;
    } else if (*input_stream_ >> current_byte_) {
        bits_left_ = CHAR_BIT;
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

size_t Reader::GetNBit(size_t num) {
    size_t result = 0;
    for (size_t i = 0; i < num; ++i) {
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
}

void Reader::SetInputStream(std::string_view filename) {
    if (has_stream_ownership_) {
        delete input_stream_;
    }
    input_stream_ = new std::ifstream(filename.data());
    has_stream_ownership_ = true;
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
