#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include "ICommand.h"
#include <string>

namespace robo
{
  class HelpCommand final : public ICommand
  {
  public:
    virtual std::string operator()(const std::string& command);
  };
}

#endif /* HELP_COMMAND_H */