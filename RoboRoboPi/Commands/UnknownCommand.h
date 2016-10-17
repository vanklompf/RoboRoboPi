#ifndef UNKNOWN_COMMAND_H
#define UNKNOWN_COMMAND_H

#include "ICommand.h"

namespace robo
{
  class UnknownCommand final : public ICommand
  {
  public:
    virtual std::string operator()(const std::string& command);
  };
}
#endif /* UNKNOWN_COMMAND_H */