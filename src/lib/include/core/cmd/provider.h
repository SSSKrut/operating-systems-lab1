// provider.h
#pragma once

#include <memory>

#include "core/command.h"

namespace console {
/**
 * @brief CommandProvider interface provides a factory method to create a new Command object
 *
 * The CommandProvider interface provides a factory method to create a new Command object.
 * The CommandProvider is used to create a new Command object when a command is executed
 * in the shell.
 */
class CommandProvider {
   public:
    virtual ~CommandProvider() = default;
    virtual std::unique_ptr<Command> create() = 0;
};
}  // namespace console