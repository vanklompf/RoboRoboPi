#ifndef TELL_COMMAND_H
#define TELL_COMMAND_H

#include "ICommand.h"

namespace robo
{
  class TellCommand final : public ICommand
  {
  public:
    std::string operator()(const std::string& command);
  };
}

#endif /* TELL_COMMAND_H */