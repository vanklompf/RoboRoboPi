#include "commands/LedCommand.h"

#include "Gpio.h"
#include "logger.h"
#include <string>

namespace robo
{
  LedCommand::LedCommand(IGpio& gpio) : m_gpio(gpio){}

  const std::string LedCommand::operator()(const std::string& command)
  {
    LogDebug("Executing LedCommand(\"%s\")", command.c_str());

    return "ok";
  }


  const std::string LedCommand::GetHelp() const
  {
    return "Blinks LEDs\n";
  }
}

