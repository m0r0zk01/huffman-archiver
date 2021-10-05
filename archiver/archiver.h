#pragma once

#include "../reader/reader.h"
#include "../writer/writer.h"
#include "../trie/trie.h"

#include <iostream>
#include <string>
#include <unordered_map>

class Archiver {
public:
    const int FILENAME_END = 256;
    const int ONE_MORE_FILE = 257;
    const int ARCHIVE_END = 258;

protected:
    Reader* reader_ = nullptr;
    Writer* writer_ = nullptr;

    Archiver(Reader* reader, Writer* writer) : reader_(reader), writer_(writer) {}
};
