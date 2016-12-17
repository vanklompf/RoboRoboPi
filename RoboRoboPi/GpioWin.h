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
    void LedOn(led_t pin) const;
    void LedOff(led_t pin) const;

    servo_status_t SetAngle(int16_t angle) const;
    servo_status_t StepLeft() const;
    servo_status_t StepRight() const;
    const char* GetStatusText(servo_status_t status) const;
  };
}

#endif /* GPIO_WIN_H */
