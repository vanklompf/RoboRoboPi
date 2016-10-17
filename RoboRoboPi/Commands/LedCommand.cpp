#include "LedCommand.h"

#include "gpio.h"
#include "logger.h"
#include <string>

namespace robo
{
  LedCommand::LedCommand(Gpio & gpio) : m_gpio(gpio){}

  std::string LedCommand::operator()(const std::string& command)
  {
    LogDebug("Executing LedCommand(\"%s\")", command.c_str());

    return "ok";
  }
}

