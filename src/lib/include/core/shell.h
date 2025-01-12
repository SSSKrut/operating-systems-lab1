// shell.h
#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "core/command.h"
#include "core/executor.h"

namespace console {
struct ShellHistoryStruct {
    std::vector<std::string> args;
    std::string output;
};

struct ExecutionReturn {
    int status;
    double elapsed;
};

/**
 * @brief ShellCommandStruct struct provides a shell command structure
 *
 * The ShellCommandStruct struct provides a shell command structure.
 * The struct is used to store a separate shell command with its arguments.
 */
struct ShellCommandStruct {
    bool is_background_task{false};
    std::vector<std::string> args;
};

/**
 * @brief ShellQueueStruct struct provides a queue of shell commands
 *
 * The ShellQueueStruct struct provides a queue of shell commands.
 * The struct is used to store a list of shell commands that are executed
 * in the shell one after the other.
 */
struct ShellQueueStruct {
    std::vector<ShellCommandStruct> commands;
};

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
class Shell {
   public:
    void run();
    void add_command(const std::string& name, std::unique_ptr<Command> command);
    void stop() { is_running_ = false; }

   private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands_;  // Is in fact an 'aliases'
    std::vector<ShellHistoryStruct> history_;
    std::string input_;
    bool is_running_{true};
    bool parse_input(const std::string& input, std::vector<std::string>& args);
    bool split_commands(const std::vector<std::string>& commands, ShellQueueStruct& queue);
    ExecutionReturn execute_command(const std::vector<std::string>& args,
                                    bool is_background_task = false);
    ExecutionReturn execute_alias(const std::vector<std::string>& args,
                                  bool is_background_task = false);
    ExecutionReturn execute(const ShellQueueStruct& queue);
    void exit();
    bool is_aliased(const std::string& command);
};

}  // namespace console