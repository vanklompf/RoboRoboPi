#ifndef TELL_COMMAND_H
#define TELL_COMMAND_H

#include "commands/ICommand.h"
#include <string>

namespace robo
{
  class TellCommand final : public ICommand
  {
  public:
    const std::string operator()(const std::string& command);
    const std::string GetHelp() const;
  };
}

#endif /* TELL_COMMAND_H */