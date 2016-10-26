#ifndef UNKNOWN_COMMAND_H
#define UNKNOWN_COMMAND_H

#include "commands/ICommand.h"
#include <string>

namespace robo
{
  class UnknownCommand final : public ICommand
  {
  public:
    const std::string operator()(const std::string& command);
    const std::string GetHelp() const { return std::string(); };
  };
}
#endif /* UNKNOWN_COMMAND_H */