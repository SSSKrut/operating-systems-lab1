// exit_command.cpp

#include "commands/exit_command.h"

#include <iostream>
#include <vector>

namespace console {
int ExitCommand::execute(const std::vector<std::string>& args) {
    (void)args;
    shell_.stop();
    return 0;
};
}  // namespace console