#include "GpioPi.h"

#include <pigpio.h>
#include "logger.h"
#include <map>
#include <cstdint>

namespace robo
{
  static const std::map<led_t, unsigned int> LedMap
  {
    { led_t::ORANGE_LED, 8 },
    { led_t::YELLOW_LED, 23 }
  };

  void GpioPi::Init() const
  {
    if (gpioInitialise() < 0)
    {
      LogDebug("Gpio init failed");
    }

    for (auto pin : LedMap)
    {
      gpioSetMode(pin.second, PI_OUTPUT);
    }
  }

  void GpioPi::LedOn(led_t led) const
  {
    auto ledPin = LedMap.find(led);
    if (ledPin != LedMap.end())
    {
      gpioWrite(ledPin->second, 1);
    }
  }

  void GpioPi::LedOff(led_t led) const
  {
    auto ledPin = LedMap.find(led);
    if (ledPin != LedMap.end())
    {
      gpioWrite(ledPin->second, 1);
    }
  }

  servo_status_t GpioPi::SetAngle(int16_t angle) const
  {
    return servo_status_t::SERVO_OK;
  }

  servo_status_t GpioPi::StepLeft() const
  {
    return servo_status_t::SERVO_OK;
  }

  servo_status_t GpioPi::StepRight() const
  {
    return servo_status_t::SERVO_OK;
  }

  const char* GpioPi::GetStatusText(servo_status_t status) const
  {
    return "some error";
  }
}