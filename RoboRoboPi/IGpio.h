#ifndef I_GPIO_H
#define I_GPIO_H
#include <stdint.h>

namespace robo
{
  enum class led_t : uint8_t
  {
    RED_LED,
    GREEN_LED,
    YELLOW_LED,
    ORANGE_LED,
    INVALID_LED,
  };

  enum class led_mode_t : uint8_t
  {
    LED_ON,
    LED_OFF,
    LED_BLINK_FAST,
    LED_BLINK_SLOW,
    LED_FADE
  };

  class IGpio
  {
  public:
    virtual void Init() const = 0;
    virtual void LedOn(led_t led) const = 0;
    virtual void LedOff(led_t led) const = 0;
    virtual void SetLed(led_t led, led_mode_t mode) const = 0;

    virtual void SetAsOutput(uint8_t pin)  const = 0;
    virtual void SetAsInput(uint8_t pin)  const = 0;


    virtual void SetServo(uint8_t pin, uint32_t pos)  const = 0;
    virtual void SetPwmFrequency(uint8_t pin, uint32_t freq)  const = 0;
    virtual void SetPwmRange(uint8_t pin, uint32_t range)  const = 0;
    virtual void SetPwmDutyCycle(uint8_t pin, uint32_t dutycycle)  const = 0;
  };
}

//gpioSetPWMfrequency(25, 400);
//gpioSetPWMrange(25, 2500);

#endif /* I_GPIO_H */