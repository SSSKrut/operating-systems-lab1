// command.h
#pragma once
#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>
namespace console {
/**
 * @brief Command interface provides a method to execute a command
 *
 * The Command interface provides a method to execute a command.
 * The Command interface is used to define the command execution behavior
 * for the shell commands.
 */
class Command {
   public:
    virtual ~Command() = default;
    virtual int execute(const std::vector<std::string>& args) = 0;
};

}  // namespace console