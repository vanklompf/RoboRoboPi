#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>
#include <string>

namespace robo
{
  class IGpio;


  enum class servo_status_t : uint8_t
  {
    SERVO_OK,
    SERVO_OUT_OF_RANGE,
    SERVO_ERROR
  };

  class Servo
  {
  public:
    Servo(IGpio& gpio, uint8_t servo_pin);
    void Init();

    servo_status_t SetAngle(int16_t angle);
    servo_status_t StepLeft();
    servo_status_t StepRight();
    std::string GetStatusText(servo_status_t status) const;

  private:
    void SetServoPin(uint32_t);

    IGpio& m_gpio;
    const uint8_t SERVO_PIN;
    uint32_t m_servo_pos;
    const uint32_t MIN_POS = 0;
    const uint32_t MAX_POS = 0;
  };
}

#endif /* SERVO_H */