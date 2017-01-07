#include "GpioPi.h"

#include <pigpio.h>
#include "logger.h"
#include <map>
#include <cstdint>

namespace robo
{
  static const std::map<led_t, unsigned int> LedMap
  {
    { led_t::YELLOW_LED, 25 },
    { led_t::ORANGE_LED, 7 }
  };

  void GpioPi::Init() const
  {
    LogDebug("GpioPi::Init()");
    if (gpioInitialise() < 0)
    {
      LogDebug("GpioPi::Init() failed");
    }

    for (auto pin : LedMap)
    {
      SetAsOutput(pin.second);
    }
  }

  GpioPi::~GpioPi()
  {
    LogDebug("Terminating GPIO()");
    gpioTerminate();
  }

  void GpioPi::LedOn(led_t led) const
  {
    auto ledPin = LedMap.find(led);
    if (ledPin != LedMap.end())
    {
      SetPinHigh(ledPin->second);
    }
  }

  void GpioPi::LedOff(led_t led) const
  {
    auto ledPin = LedMap.find(led);
    if (ledPin != LedMap.end())
    {
      SetPinLow(ledPin->second);
    }
  }

  void GpioPi::SetPinHigh(unsigned int pin) const
  {
    LogDebug("Setting pin: %d HIGH", pin);
    gpioWrite(pin, 1);
  }

  void GpioPi::SetPinLow(unsigned int pin) const
  {
    LogDebug("Setting pin: %d LOW", pin);
    gpioWrite(pin, 0);
  }

  void GpioPi::SetLed(led_t led, led_mode_t mode) const
  {
  }

  void GpioPi::SetAsOutput(uint8_t pin) const
  {
    LogDebug("PIN: %d set as OUTPUT", pin);
    gpioSetMode(pin, PI_OUTPUT);
  }

  void GpioPi::SetAsInput(uint8_t pin) const
  {
    LogDebug("PIN: %d set as INPUT", pin);
    gpioSetMode(pin, PI_INPUT);
  }

  void GpioPi::SetServo(uint8_t pin, uint32_t pos) const
  {
    LogDebug("PIN: %d set to pos: %d", pin, pos);
    gpioServo(pin, pos);
  }

  void GpioPi::SetPwmFrequency(uint8_t pin, uint32_t freq)  const
  {
    LogDebug("PIN: %d set PWM freq: %d", pin, freq);
    gpioSetPWMfrequency(pin, freq);
  }

  void GpioPi::SetPwmRange(uint8_t pin, uint32_t range)  const
  {
    LogDebug("PIN: %d set PWM range: %d", pin, range);
    gpioSetPWMrange(pin, range);
  }

  void GpioPi::SetPwmDutyCycle(uint8_t pin, uint32_t dutycycle)  const
  {
    LogDebug("PIN: %d set PWM dutycycle: %d", pin, dutycycle);
    gpioPWM(pin, dutycycle);
  }
}