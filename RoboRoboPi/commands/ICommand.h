#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>

namespace robo
{
  class ICommand
  {
  public:
    virtual const std::string operator()(const std::string& command) = 0;
    virtual const std::string GetHelp() const = 0;
  };
}
#endif /* ICOMMAND_H */