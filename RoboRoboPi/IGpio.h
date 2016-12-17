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
  };

  enum class servo_status_t : uint8_t
  {
    SERVO_OK,
    SERVO_OUT_OF_RANGE,
    SERVO_ERROR
  };

  class IGpio
  {
  public:
    virtual void Init() const = 0;
    virtual void LedOn(led_t pin) const = 0;
    virtual void LedOff(led_t pin) const = 0;

    virtual servo_status_t SetAngle(int16_t angle) const = 0;
    virtual servo_status_t StepLeft() const = 0;
    virtual servo_status_t StepRight() const = 0;
    virtual const char* GetStatusText(servo_status_t status) const = 0;
  };
}

#endif /* I_GPIO_H */