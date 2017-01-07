#include "Servo.h"
#include "IGpio.h"
#include "logger.h"
#include <string>
#include <chrono>
#include <thread>

namespace robo
{
  Servo::Servo(IGpio& gpio, uint8_t servo_pin) : m_gpio(gpio), SERVO_PIN(servo_pin), m_servo_pos(1500) {};

  void Servo::Init()
  {
    LogDebug("Servo::Init()");
    m_gpio.SetAsOutput(8);

    SetServoPin(m_servo_pos);
  }

  void Servo::SetServoPin(uint32_t pos)
  {
    m_gpio.SetServo(SERVO_PIN, pos);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m_gpio.SetServo(SERVO_PIN, 0);
  }

  servo_status_t Servo::SetAngle(int16_t angle)
  {
    return servo_status_t::SERVO_OK;
  }

  servo_status_t Servo::StepLeft()
  {
    m_servo_pos -= 25;
    SetServoPin(m_servo_pos);
    return servo_status_t::SERVO_OK;
  }

  servo_status_t Servo::StepRight()
  {
    m_servo_pos += 25;
    SetServoPin(m_servo_pos);
    return servo_status_t::SERVO_OK;
  }

  std::string Servo::GetStatusText(servo_status_t status) const
  {
    return "st";
  }
}