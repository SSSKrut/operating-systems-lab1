// cd_command.h
#pragma once

#include "core/command.h"

namespace console {
class CdCommand : public Command {
   public:
    int execute(const std::vector<std::string>& args) override;
};
}  // namespace console