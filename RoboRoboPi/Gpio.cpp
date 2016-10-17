#include "Gpio.h"

#include "wiringPi.h"
#include <map>
#include <cstdint>

namespace robo
{
  /* todo: correct values */
  const std::map<gpio_func_t, int> GpioMap
  {
    { gpio_func_t::RED_LED,    16 },
    { gpio_func_t::GREEN_LED,  17 },
    { gpio_func_t::ORANGE_LED, 18 },
    { gpio_func_t::YELLOW_LED, 19 },
    { gpio_func_t::BEEPER,     20 }
  };

  void Gpio::Init() const
  {
    for (auto gpio : GpioMap)
    {
      pinMode(gpio.second, OUTPUT);
    }
  }

  bool Gpio::LedOn(gpio_func_t led) const
  {
    return false;
  }

  bool Gpio::LedOff(gpio_func_t led) const
  {
    return false;
  }

  bool Gpio::LedToggle(gpio_func_t led) const
  {
    return false;
  }

  bool Gpio::Beep() const
  {
    return false;
  }
}