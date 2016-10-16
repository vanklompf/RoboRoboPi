#include "ServoCommand.h"
#include "servo.h"
#include "logger.h"

#include<string>

namespace robo
{
  ServoCommand::ServoCommand(Servo& servo) : m_servo(servo){}

  std::string ServoCommand::operator()(const std::string& command)
  {
    LogDebug("Executing ServoCommand(\"%s\")", command.c_str());

    Servo::servo_status_t status = Servo::SERVO_ERROR;
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
        return "Unknown parameters: " + command;
      }
    }

    return m_servo.getStatusText(status);
  }
}