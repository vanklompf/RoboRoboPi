#include "commands/ServoCommand.h"
#include "servo.h"
#include "logger.h"

#include<string>

namespace robo
{
  ServoCommand::ServoCommand(Servo& servo) : m_servo(servo){}

  const std::string ServoCommand::operator()(const std::string& command)
  {
    LogDebug("Executing ServoCommand(\"%s\")", command.c_str());

    auto status = servo_status_t::SERVO_ERROR;
    char param = command.front();

    if ((param <= '9') && (param >= '0'))
    {
      int value = ((param - '0') * 10) - 42;
      status = m_servo.SetAngle(value);
    }
    else
    {
      switch (param)
      {
      case 'l':
        status = m_servo.StepLeft();
        break;
      case 'r':
        status = m_servo.StepRight();
        break;
      default:
        return "[ServoCommand] Unknown parameters: " + command;
      }
    }

    return m_servo.getStatusText(status);
  }
  const std::string ServoCommand::GetHelp() const
  {
    return
      "Controls Servomotor\n"
      "Parameters:\n"
      "\tl - rotate step left\n"
      "\tr - rotate step right\n"
      "\t0-9 - rotate to defined position\n"
      ;
  }
}