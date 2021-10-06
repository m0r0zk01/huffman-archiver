#include <string>
#include <unordered_map>
#include <vector>

class Parser {
public:
    Parser(int argc, char** argv);

    bool Exists(const std::string& arg) const;
    const std::vector<std::string>& GetValues(const std::string& arg) const;
    void AddRule(const std::string& arg, int _min, int _max=-1);
    void CheckRules() const;
    int ArgumentsAmount() const;

private:
    int argc_;
    std::unordered_map<std::string, std::vector<std::string>> parsed_arguments_;
    std::unordered_map<std::string, std::pair<int, int>> values_rules_;
};