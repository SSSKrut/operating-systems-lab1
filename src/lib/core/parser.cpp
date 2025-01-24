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
}  // namespace console