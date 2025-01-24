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
        std::cout << color::cyan() << "shell>" << color::reset() << " ";

        if (!std::getline(std::cin, input)) break;

        std::vector<std::string> args;
        if (!parse_input(input, args)) continue;

        if (args.empty()) continue;

        ShellQueueStruct queue;
        split_commands(args, queue);

        ExecutionReturn returned = execute(queue);

        std::cout << color::green() << "status: " << returned.status
                  << " eta: " << returned.elapsed;
        std::cout << color::reset() << std::endl;
    }
}

bool Shell::parse_input(const std::string& input, std::vector<std::string>& args) {
    InputParser parser;
    parser.parse(input, args);
    return !args.empty();
}

bool Shell::split_commands(const std::vector<std::string>& commands, ShellQueueStruct& queue) {
    std::vector<std::string> command;
    for (const auto& word : commands) {
        if (word.empty()) continue;
        if (word == "" || word == " ") continue;

        if (word == "&&") {
            ShellCommandStruct shell_command;
            shell_command.args = command;

            queue.commands.push_back(shell_command);
            command.clear();
            continue;
        }

        if (word == "&") {
            ShellCommandStruct shell_command;
            shell_command.args = command;
            shell_command.is_background_task = true;

            queue.commands.push_back(shell_command);
            command.clear();
            continue;
        }

        command.push_back(word);
    }

    if (!command.empty()) {
        ShellCommandStruct shell_command;
        shell_command.args = command;
        queue.commands.push_back(shell_command);
    }

    return true;
}

void Shell::add_command(const std::string& name, std::unique_ptr<Command> command) {
    commands_[name] = std::move(command);
}

ExecutionReturn Shell::execute_command(const std::vector<std::string>& args,
                                       bool is_background_task) {
    ExecutionReturn ret = {.status = -1, .elapsed = 0.0};
    Executor executor;
    ret.status = executor.execute(args, is_background_task);
    ret.elapsed = executor.get_execution_time();

    return ret;
}

void Shell::exit() { is_running_ = false; }

bool Shell::is_aliased(const std::string& command) {
    return commands_.find(command) != commands_.end();
}

ExecutionReturn Shell::execute_alias(const std::vector<std::string>& args,
                                     bool is_background_task) {
    (void)is_background_task;
    ExecutionReturn ret = {.status = -1, .elapsed = 0.0};
    auto it = commands_.find(args[0]);
    if (it == commands_.end()) return ret;

    Executor executor;
    ret.status = executor.execute(*it->second.get(), args);
    ret.elapsed = executor.get_execution_time();

    return ret;
}

ExecutionReturn Shell::execute(const ShellQueueStruct& queue) {
    ExecutionReturn ret = {.status = 0, .elapsed = 0.0};
    double elapsed = 0.0;
    for (const auto& command : queue.commands) {
        ret = is_aliased(command.args[0])
                  ? execute_alias(command.args, command.is_background_task)
                  : execute_command(command.args, command.is_background_task);
        ret.elapsed += elapsed;
        elapsed = ret.elapsed;
        if (ret.status != 0) break;
    }

    return ret;
}

}  // namespace console