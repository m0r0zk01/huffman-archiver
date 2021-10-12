#include <string>
#include <string_view>

struct Exception : public std::exception {
    std::string s;
    Exception(const std::string_view s) : s(s) {}
    ~Exception() throw () {}
    const char* what() const noexcept override { return s.c_str(); }
};