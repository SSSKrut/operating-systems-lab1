#include "core/executor.h"

#include <sys/wait.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "utils/utils.h"

namespace console {

void clean_up(std::vector<char*>& c_args) {
    for (char* arg : c_args) {
        free(arg);
    }
    c_args.clear();
}
int Executor::execute(const std::vector<std::string>& args) {
    if (args.empty()) return -1;

    start_time_ = std::chrono::high_resolution_clock::now();

    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << color::red() << "failed to fork\n" << color::reset();
        end_time_ = std::chrono::high_resolution_clock::now();
        return 1;
    } else if (pid == 0) {
        std::vector<char*> c_args;
        for (const auto& arg : args) {
            c_args.push_back(strdup(arg.c_str()));
        }
        c_args.push_back(nullptr);

        execvp(c_args[0], c_args.data());
        std::cerr << color::red() << "failed to execute command\n" << color::reset();

        clean_up(c_args);
        exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    end_time_ = std::chrono::high_resolution_clock::now();

    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

int Executor::execute(console::Command& command, const std::vector<std::string>& args) {
    return command.execute(args);
}

double Executor::get_execution_time() const {
    std::chrono::duration<double> elapsed = end_time_ - start_time_;
    return elapsed.count();
}

}  // namespace console