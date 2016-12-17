#include "GpioWin.h"

#include "logger.h"
#include <map>
#include <cstdint>

namespace robo
{
  void GpioWin::Init() const
  {
  }

  void GpioWin::LedOn(led_t led) const
  {
  }

  void GpioWin::LedOff(led_t led) const
  {
  }

  servo_status_t GpioWin::SetAngle(int16_t angle) const
  {
    return servo_status_t::SERVO_OK;
  }

  servo_status_t GpioWin::StepLeft() const
  {
    return servo_status_t::SERVO_OK;
  }

  servo_status_t GpioWin::StepRight() const
  {
    return servo_status_t::SERVO_OK;
  }

  const char* GpioWin::GetStatusText(servo_status_t status) const
  {
    return "some error";
  }
}