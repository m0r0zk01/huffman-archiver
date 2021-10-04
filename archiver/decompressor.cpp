#include "compressor.h"

Decompressor::Decompressor() {}

Decompressor::Decompressor(std::istream& is) {
    reader_.SetInputStream(is);
}

Decompressor::Decompressor(std::string_view filename) {
    reader_.SetInputStream(filename);
}

bool Decompressor::DecompressNextFile() {
    size_t symbols_count = reader_.GetNBit(9);
    std::vector<size_t> values;
    for (size_t i = 0; i < symbols_count; ++i) {
        values.push_back(reader_.GetNBit(9));
    }


}

void Decompressor::Decompress() {
    while (DecompressNextFile()) {}
}
