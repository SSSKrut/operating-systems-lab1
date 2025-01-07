#pragma once
#include <string>
#include <vector>

namespace console {
/**
 * @brief InputParser class provides functionality to parse input strings into arguments
 *
 * The InputParser class provides functionality to parse input strings into arguments.
 * The class is used to parse input strings into arguments that can be used to execute
 * commands in the shell.
 */
class InputParser {
   public:
    void parse(const std::string& input, std::vector<std::string>& args);
    static std::vector<char*> to_c_args(const std::vector<std::string>& args);
};
}  // namespace console