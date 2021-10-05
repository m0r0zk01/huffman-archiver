#pragma once

#include "../reader/reader.h"
#include "../writer/writer.h"
#include "../trie/trie.h"

#include <iostream>
#include <string>
#include <unordered_map>

const int FILENAME_END = 256;
const int ONE_MORE_FILE = 257;
const int ARCHIVE_END = 258;

class Archiver {
public:

protected:
    Reader reader_;
    Writer writer_;
};
