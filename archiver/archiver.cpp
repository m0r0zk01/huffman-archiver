#include "archiver.h"

void Archiver::HuffmanCode::AddZeroes(size_t amount) {
    for (size_t i = 0; i < amount; ++i) {
        code.push_back(false);
    }
}

void Archiver::HuffmanCode::Increment() {
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

std::vector<bool> Archiver::HuffmanCode::GetData() const {
    return code;
}

size_t Archiver::HuffmanCode::Size() const {
    return code.size();
}

Archiver::HuffmanCode::HuffmanCode(std::vector<bool>& bits) : code(bits) {}
