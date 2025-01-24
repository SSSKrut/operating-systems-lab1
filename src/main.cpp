// main.cpp

#include <memory>

#include "commands/cd_command.h"
#include "commands/exit_command.h"
#include "core/shell.h"
int main() {
    console::Shell shell;
    shell.add_command("cd", std::make_unique<console::CdCommand>());
    shell.add_command("exit", std::make_unique<console::ExitCommand>(shell));

    shell.run();
    return 0;
}
