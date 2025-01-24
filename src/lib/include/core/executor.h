#pragma once
#include <chrono>
#include <string>
#include <vector>

#include "core/command.h"

namespace console {
/**
 * @brief Executor class provides functionality to execute shell commands
 *
 * The Executor class provides functionality to execute shell commands.
 * The class is used to execute shell commands and measure the execution time.
 */
class Executor {
   public:
    int execute(const std::vector<std::string>& args);
    int execute(const std::vector<std::string>& args, bool is_background_task);
    int execute(console::Command& command, const std::vector<std::string>& args,
                bool is_background_task = false);
    double get_execution_time() const;

   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time_;
};
}  // namespace console