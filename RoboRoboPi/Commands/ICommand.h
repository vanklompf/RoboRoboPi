#ifndef COMMAND_H
#define COMMAND_H

#include <string>

namespace robo
{
  class ICommand
  {
  public:
    virtual std::string operator()(const std::string& command) = 0;
  };
}
#endif /* COMMAND_H */