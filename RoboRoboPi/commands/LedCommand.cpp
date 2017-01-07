#include "commands/LedCommand.h"

#include "IGpio.h"
#include "logger.h"
#include <string>

namespace robo
{
  LedCommand::LedCommand(IGpio& gpio) : m_gpio(gpio){}

  const std::string LedCommand::operator()(const std::string& command)
  {
    LogDebug("Executing LedCommand(\"%s\")", command.c_str());

    auto colorCode = command[0];
    auto mode = command[1];
    auto color = GetColor(colorCode);

    if (mode == '0')
    {
      m_gpio.LedOff(color);
    }
    else
    {
      m_gpio.LedOn(color);
    }

    return "OK";
  }

  led_t LedCommand::GetColor(char code)
  {
    const std::map<char, led_t> LedMap
    {
      { 'y', led_t::YELLOW_LED },
      { 'o', led_t::ORANGE_LED },
      { 'g', led_t::GREEN_LED },
      { 'r', led_t::RED_LED }
    };

    auto ledColor = LedMap.find(code);
    if (ledColor != LedMap.end())
    {
      return ledColor->second;
    }
    return led_t::INVALID_LED;
  }

  const std::string LedCommand::GetHelp() const
  {
    return "Blinks LEDs\n";
  }
}

