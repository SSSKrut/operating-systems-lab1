#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "commands/cd_command.h"
#include "commands/exit_command.h"
#include "core/shell.h"
#include "utils/utils.h"
using namespace console::color;
int main() {
    console::Shell shell;
    shell.add_command("cd", std::make_unique<console::CdCommand>());
    shell.add_command("exit", std::make_unique<console::ExitCommand>(shell));
    // shell.add_command("history", std::make_unique<HistoryCommand>());
    // shell.add_command("ls", std::make_unique<LsCommand>());
    shell.run();
    return 0;
}
