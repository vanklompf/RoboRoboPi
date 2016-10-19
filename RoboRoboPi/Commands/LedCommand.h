#ifndef LED_COMMAND_H
#define LED_COMMAND_H

#include "ICommand.h"
#include <string>

namespace robo
{
  class Gpio;

  class LedCommand final : public ICommand
  {
  public:
    LedCommand(Gpio& gpio);
    virtual std::string operator()(const std::string& command);

  private:
    Gpio& m_gpio;
  };
}

#endif /* LED_COMMAND_H */