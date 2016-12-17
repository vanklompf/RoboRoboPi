#ifndef SERVO_COMMAND_H
#define SERVO_COMMAND_H

#include "commands/ICommand.h"
#include <string>

namespace robo
{
  class IGpio;

  class ServoCommand final : public ICommand
  {
  public:
    ServoCommand(IGpio& gpio);
    const std::string operator()(const std::string& command);
    const std::string GetHelp() const;

  private:
    IGpio& m_gpio;
  };
}

#endif /* SERVO_COMMAND_H */