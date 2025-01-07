#pragma once
#include <chrono>
#include <string>
#include <vector>

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
    double get_execution_time() const;

   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time_;
};
}  // namespace console