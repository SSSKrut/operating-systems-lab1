#include "core/parser.h"

#include <sstream>

namespace console {
void InputParser::parse(const std::string& input, std::vector<std::string>& args) {
    std::istringstream iss(input);
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
}
std::vector<char*> InputParser::to_c_args(const std::vector<std::string>& args) {
    std::vector<char*> c_args;
    for (const auto& arg : args) {
        c_args.push_back(const_cast<char*>(arg.c_str()));
    }
    c_args.push_back(nullptr);
    return c_args;
}
}  // namespace console