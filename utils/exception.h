struct Exception : public std::exception
{
    std::string s;
    Exception(std::string s) : s(s) {}
    ~Exception() throw () {}
    const char* what() const throw() { return s.c_str(); }
};