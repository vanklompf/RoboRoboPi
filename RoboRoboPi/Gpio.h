#ifndef GPIO_CONFIGURATION_H
#define GPIO_CONFIGURATION_H
#include <cstdint>

namespace robo
{
  enum class gpio_func_t : uint8_t
  {
    RED_LED,
    GREEN_LED,
    YELLOW_LED,
    ORANGE_LED,
    BEEPER
  };

  class Gpio
  {
  public:
    void Init() const;
    bool LedOn(gpio_func_t led) const;
    bool LedOff(gpio_func_t led) const;
    bool LedToggle(gpio_func_t led) const;
    bool Beep() const;
  };
}

#endif /* GPIO_CONFIGURATION_H */