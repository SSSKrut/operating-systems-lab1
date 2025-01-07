// shell.h
#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "core/command.h"
#include "core/executor.h"

/**
 * @brief Shell class provides command-line interface functionality with command and alias support
 *
 * The Shell class implements a command-line interface with history tracking and command execution.
 * It supports two types of executable items:
 * - Commands: Pre-defined built-in shell commands that come with the shell implementation
 * - Aliases: Custom command implementations that can be added by the library user
 *
 * @note Commands are the default shell operations that are built into the shell.
 *       Aliases are user-defined command implementations that extend shell functionality.
 *
 * The class maintains:
 * - A map of available commands
 * - Command execution history
 * - Current input state
 * - Shell running state
 */
namespace console {
struct ShellHistoryStruct {
    std::vector<std::string> args;
    std::string output;
};
struct ExecutionReturn {
    int status;
    double elapsed;
};

class Shell {
   public:
    void run();
    void add_command(const std::string& name, std::unique_ptr<Command> command);

   private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands_;  // Is in fact an 'aliases'
    std::vector<ShellHistoryStruct> history_;
    std::string input_;
    bool is_running_{true};
    bool parse_input(const std::string& input, std::vector<std::string>& args);
    ExecutionReturn execute_command(const std::vector<std::string>& args);
    ExecutionReturn execute_alias(const std::vector<std::string>& args);
    void exit();
    bool is_aliased(const std::string& command);
};

}  // namespace console