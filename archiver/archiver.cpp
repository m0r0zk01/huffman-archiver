#include "archiver.h"

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