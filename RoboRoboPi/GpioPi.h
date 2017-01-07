#ifndef GPIO_PI_H
#define GPIO_PI_H
#include <cstdint>
#include "IGpio.h"

namespace robo
{
  class GpioPi : public IGpio
  {
  public:
    ~GpioPi();
    void Init() const;
    void LedOn(led_t pin) const;
    void LedOff(led_t pin) const;
    void SetLed(led_t led, led_mode_t mode) const;

    void SetAsOutput(uint8_t pin) const;
    void SetAsInput(uint8_t pin) const;

    void SetServo(uint8_t pin, uint32_t pos) const;
    void SetPwmFrequency(uint8_t pin, uint32_t freq)  const;
    void SetPwmRange(uint8_t pin, uint32_t range)  const;
    void SetPwmDutyCycle(uint8_t pin, uint32_t dutycycle)  const;

  private:
    void SetPinHigh(unsigned int pin) const;
    void SetPinLow(unsigned int pin) const;
  };
}

#endif /* GPIO_PI_H */