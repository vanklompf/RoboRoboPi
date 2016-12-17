#ifndef LED_COMMAND_H
#define LED_COMMAND_H

#include "commands/ICommand.h"
#include <string>

namespace robo
{
  class IGpio;

  class LedCommand final : public ICommand
  {
  public:
    LedCommand(IGpio& gpio);
    const std::string operator()(const std::string& command);
    const std::string GetHelp() const;

  private:
    IGpio& m_gpio;
  };
}

#endif /* LED_COMMAND_H */