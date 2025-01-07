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

        // if (is_aliased(args[0])) {
        //     execute_alias(args);
        // } else {
        //     execute_command(args);
        // }

        if (is_aliased(args[0])) {
            ExecutionReturn returned = execute_alias(args);
            std::cout << color::cyan() << "status: " << returned.status << "\n" << color::reset();
        } else {
            ExecutionReturn returned = execute_command(args);
            std::cout << color::cyan() << "status: " << returned.status << "\n" << color::reset();
            std::cout << color::cyan() << "eta: " << returned.elapsed << "s\n" << color::reset();
            std::cout << std::endl;
        }

        // ExecutionReturn returned =
        //     is_aliased(args[0]) ? execute_alias(args) : execute_command(args);
        // std::cout << color::cyan() << "status: " << returned.status << "\n" << color::reset();
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

// int Shell::execute_command(const std::vector<std::string>& args) {
//     auto it = commands_.find(args[0]);
//     if (it != commands_.end()) {
//         return it->second->execute(args);
//     }

//     auto start = std::chrono::high_resolution_clock::now();
//     pid_t pid = fork();

//     if (pid == -1) {
//         std::cerr << color::red() << "failed to fork\n" << color::reset();
//         return 1;
//     }

//     if (pid == 0) {
//         std::vector<char*> c_args;
//         for (const auto& arg : args) {
//             c_args.push_back(strdup(arg.c_str()));
//         }
//         c_args.push_back(nullptr);

//         execvp(c_args[0], c_args.data());
//         std::cerr << color::red() << "failed to execute command\n" << color::reset();

//         clean_up(c_args);
//         exit(1);
//     }

//     int status;
//     waitpid(pid, &status, 0);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> elapsed = end - start;
//     std::cout << color::cyan() << "eta: " << elapsed.count() << "s\n" << color::reset();
// }

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
    if (it != commands_.end()) {
        return execute_command(args);
    }
    return ExecutionReturn{-1, 0.0};
}

}  // namespace console