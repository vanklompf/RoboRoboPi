#ifndef SERVO_H
#define SERVO_H
#include <cstdint>

namespace robo
{
  enum servo_status_t
  {
    SERVO_OK,
    SERVO_OUT_OF_RANGE,
    SERVO_ERROR
  };

  class Servo
  {
  public:
    void init();
    const char* getStatusText(servo_status_t status) const;
    servo_status_t SetAngle(int16_t angle);
    servo_status_t StepLeft();
    servo_status_t StepRight();

  private:
    int m_gpio_value;

    servo_status_t setGpioRegister(int16_t value);
    int angleToGpioValue(int16_t angle) const;
    int16_t gpioValueToAngle(int value) const;
  };
}
#endif //SERVO_H
