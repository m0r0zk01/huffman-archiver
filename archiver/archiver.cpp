#include "archiver.h"

void Archiver::Code::AddBit(bool bit) {
    code.push_back(bit);
}

void Archiver::Code::AddZeroes(size_t amount) {
    for (size_t i = 0; i < amount; ++i) {
        code.push_back(false);
    }
}

void Archiver::Code::Increment() {
    size_t i = code.size() - 1;
    while (i >= 0) {
        if (!code[i]) {
            code[i] = true;
            break;
        } else {
            code[i] = false;
        }
        if (i == 0) {
            code.insert(code.begin(), true);
            break;
        }
        i--;
    }
}

std::vector<bool> Archiver::Code::GetData() const {
    return code;
}

size_t Archiver::Code::Size() const {
    return code.size();
}

Archiver::Code::Code(std::vector<bool>& bits) : code(bits) {}

Archiver::Archiver(Reader* reader, Writer* writer) {
    if (reader) {
        ChangeReader(reader);
    } else {
        reader_ = new Reader;
    }
    if (writer) {
        ChangeWriter(writer);
    } else {
        writer_ = new Writer;
    }
}

Archiver::~Archiver() {
    if (is_reader_dynamically_allocated) {
        delete reader_;
    }
    if (is_writer_dynamically_allocated) {
        delete writer_;
    }
}

void Archiver::ChangeReader(Reader* reader) {
    reader_ = reader;
    is_reader_dynamically_allocated = false;
}

void Archiver::ChangeWriter(Writer* writer) {
    writer_ = writer;
    is_writer_dynamically_allocated = false;
}