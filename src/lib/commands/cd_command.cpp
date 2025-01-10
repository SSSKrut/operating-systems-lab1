#include "commands/cd_command.h"

#include <unistd.h>

#include <iostream>
#include <vector>

namespace console {
int CdCommand::execute(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        std::cerr << "cd: missing argument\n";
        return 1;
    }
    std::cout << "Changing directory to: " << args[1] << std::endl;
    if (chdir(args[1].c_str()) == -1) {
        std::cerr << "cd: failed to change directory\n";
        return 1;
    }
    return 0;
};
}  // namespace console