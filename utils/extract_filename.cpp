#include "extract_filename.h"

#include <algorithm>

std::string ExtractFilenameFromFilepath(const std::string_view filepath) {
    if (filepath.empty()) {
        return "";
    }
    auto i1 = filepath.find_last_of('/');
    auto i2 = filepath.find_last_of('\\');
    i1 = i1 == std::string::npos ? 0 : i1;
    i2 = i2 == std::string::npos ? 0 : i2;
    auto last_slash = std::max(i1, i2);
    return filepath.substr(last_slash + (filepath[last_slash] == '\\' || filepath[last_slash] == '/')).data();
}
