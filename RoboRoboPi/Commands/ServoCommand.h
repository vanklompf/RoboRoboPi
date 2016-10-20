#ifndef SERVO_COMMAND_H
#define SERVO_COMMAND_H

#include "ICommand.h"
#include <string>

namespace robo
{
  class Servo;

  class ServoCommand final : public ICommand
  {
  public:
    ServoCommand(Servo& servo);
    const std::string operator()(const std::string& command);
    const std::string ServoCommand::GetHelp() const;

  private:
    Servo& m_servo;
  };
}

#endif /* SERVO_COMMAND_H */