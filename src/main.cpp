#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "lib/utils.h"
using namespace console::color;
int main() {
    std::string input;
    while (true) {
        std::cout << cyan() << "shell> " << reset();
        if (!std::getline(std::cin, input)) break;

        std::istringstream iss(input);
        std::vector<char *> args;
        std::string arg;
        while (iss >> arg) {
            args.push_back(strdup(arg.c_str()));
        }
        args.push_back(nullptr);

        if (args[0] == nullptr) continue;

        auto start = std::chrono::high_resolution_clock::now();

        pid_t pid = fork();
        if (pid == -1) {
            std::cerr << red() << "failed to fork\n" << reset();
            return 1;
        } else if (pid == 0) {
            execvp(args[0], args.data());
            // If all goes well, execvp never returns
            std::cerr << red() << "failed to execute command\n" << reset();
            for (char *arg : args) {
                free(arg);
            }
            args.clear();
            return 1;
        }

        int status;
        waitpid(pid, &status, 0);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "eta: " << elapsed.count() << "s\n";

        for (char *arg : args) {
            free(arg);
        }
        args.clear();
    }
    return 0;
}