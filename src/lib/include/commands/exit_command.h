// exit_command.h
#pragma once

#include "core/command.h"
#include "core/shell.h"

namespace console {
class ExitCommand : public Command {
   public:
    explicit ExitCommand(Shell& shell) : shell_(shell) {};
    int execute(const std::vector<std::string>& args) override {
        (void)args;
        shell_.stop();
        return 0;
    };

   private:
    Shell& shell_;
};
}  // namespace console