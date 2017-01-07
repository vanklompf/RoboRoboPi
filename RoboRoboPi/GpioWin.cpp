#include "GpioWin.h"

#include "logger.h"
#include <cstdint>

namespace robo
{
  void GpioWin::Init() const
  {
    LogDebug("GpioWin::Init()");
  }

  void GpioWin::SetAsOutput(uint8_t pin) const
  {
    LogDebug("PIN: %d set as OUTPUT", pin);
  }

  void GpioWin::SetAsInput(uint8_t pin) const
  {
    LogDebug("PIN: %d set as INPUT", pin);
  }

  void GpioWin::SetServo(uint8_t pin, uint32_t pos) const
  {
    LogDebug("PIN: %d set to pos: %d", pin, pos);
  }

  void GpioWin::SetPwmFrequency(uint8_t pin, uint32_t freq)  const
  {
    LogDebug("PIN: %d set PWM freq: %d", pin, freq);
  }

  void GpioWin::SetPwmRange(uint8_t pin, uint32_t range)  const
  {
    LogDebug("PIN: %d set PWM range: %d", pin, range);
  }

  void GpioWin::SetPwmDutyCycle(uint8_t pin, uint32_t dutycycle)  const
  {
    LogDebug("PIN: %d set PWM dutycycle: %d", pin, dutycycle);
  }
}