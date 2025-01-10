#include "core/shell.h"

#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "core/executor.h"
#include "core/parser.h"
#include "utils/utils.h"

namespace console {

void Shell::run() {
    std::string input;
    while (is_running_) {
        std::cout << color::cyan() << "shell> " << color::reset();

        if (!std::getline(std::cin, input)) break;

        std::vector<std::string> args;
        if (!parse_input(input, args)) continue;

        if (args.empty()) continue;

        ExecutionReturn returned =
            is_aliased(args[0]) ? execute_alias(args) : execute_command(args);
        std::cout << color::cyan() << "status: " << returned.status << " eta: " << returned.elapsed;
        std::cout << std::endl << color::reset();
    }
}

bool Shell::parse_input(const std::string& input, std::vector<std::string>& args) {
    InputParser parser;
    parser.parse(input, args);
    return !args.empty();
}

void Shell::add_command(const std::string& name, std::unique_ptr<Command> command) {
    commands_[name] = std::move(command);
}

ExecutionReturn Shell::execute_command(const std::vector<std::string>& args) {
    Executor executor;
    int status = executor.execute(args);
    double elapsed = executor.get_execution_time();

    return ExecutionReturn{status, elapsed};
}

void Shell::exit() { is_running_ = false; }

bool Shell::is_aliased(const std::string& command) {
    return commands_.find(command) != commands_.end();
}

ExecutionReturn Shell::execute_alias(const std::vector<std::string>& args) {
    auto it = commands_.find(args[0]);
    if (it == commands_.end()) return ExecutionReturn{-1, 0.0};

    Executor executor;
    int status = executor.execute(*it->second.get(), args);
    double elapsed = executor.get_execution_time();

    return ExecutionReturn{status, elapsed};
}

}  // namespace console