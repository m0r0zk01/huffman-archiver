#pragma once

#include "reader/reader.h"
#include "writer/writer.h"

#include <string>

class Archiver {
public:
    Archiver();

protected:
    Reader reader_;
    Writer writer_;
};

class Compressor : Archiver {
public:
    Compressor();
    Compressor(std::ostream& os);

    void AddFile(std::istream& is);
};

class Decompressor : public Archiver {

};
