#include "command_line_arguments_parser.h"
#include "exception.h"

Parser::Parser(int argc, char** argv) : argc_(argc) {
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] == '-') {
            auto& it = parsed_arguments_[static_cast<std::string>(argv[i])];
            i++;
            while (i < argc && argv[i][0] != '-') {
                it.push_back(argv[i]);
                i++;
            }
            i--;
        }
    }
}

bool Parser::Exists(const std::string& arg) const {
    return parsed_arguments_.find(arg) != parsed_arguments_.end();
}

const std::vector<std::string>& Parser::GetValues(const std::string& arg) const {
    auto it = parsed_arguments_.find(arg);
    static std::vector<std::string> empty;
    return it == parsed_arguments_.end() ? empty : it->second;
}

void Parser::AddRule(const std::string& arg, int _min, int _max) {
    if (_max == -1) {
        _max = _min;
    }
    values_rules_[arg] = {_min, _max};
}

void Parser::CheckRules() const {
    for (const auto& [arg, rule] : values_rules_) {
        auto it = parsed_arguments_.find(arg);
        if (it != parsed_arguments_.end()) {
            if (!(rule.first <= static_cast<int>(it->second.size()) &&
                  static_cast<int>(it->second.size()) <= rule.second)) {
                throw Exception("Wrong arguments. See -h for help");
            }
        }
    }
}

int Parser::ArgumentsAmount() const {
    return argc_;
}
