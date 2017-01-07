#ifndef GPIO_WIN_H
#define GPIO_WIN_H
#include <cstdint>
#include "IGpio.h"

namespace robo
{
  class GpioWin : public IGpio
  {
  public:
    void Init() const;
    void LedOn(led_t pin) const {};
    void LedOff(led_t pin) const {};
    void SetLed(led_t led, led_mode_t mode) const {};

    void SetAsOutput(uint8_t pin) const;
    void SetAsInput(uint8_t pin) const;
    void SetServo(uint8_t pin, uint32_t pos) const;
    void SetPwmFrequency(uint8_t pin, uint32_t freq)  const;
    void SetPwmRange(uint8_t pin, uint32_t range)  const;
    void SetPwmDutyCycle(uint8_t pin, uint32_t dutycycle)  const;
  };
}

#endif /* GPIO_WIN_H */
