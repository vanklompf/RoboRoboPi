#include <wiringPi.h>
#include <stdio.h>
#include "servo.h"
/*
 *  Clock and range values from
 *  http://stackoverflow.com/questions/20081286/controlling-a-servo-with-raspberry-pi-using-the-hardware-pwm-with-wiringpi
 *  Range tests:
 *  Clock: 384 Range: 30 - 115
 *  Clock: 500 Range: 25 - 80
 *  Clock: 400 Range: 29 - 111
 *  Clock: 250 Range: 46 - 178
 *  Clock: 200 Range: 57 - 223
 *  Clock: 100 Not working
 */
static const int SERVO_PIN = 1;
static const int MIN = 30;
static const int MAX = 115;
static const int ZERO = (MIN + MAX) / 2;

static constexpr char const * const arr[] = { "INFO", "WARNING", "ERROR", "CRASH" };
static const char * const error_values[] = 
{ 
  "SERVO_OK", 
  "SERVO_OUT_OF_RANGE",
  "SERVO_ERROR"
};

void Servo::init()
{
    pinMode (SERVO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(384);
    pwmSetRange(1000);

    setAngle(0);
}

Servo::servo_status_t Servo::setGpioRegister(int16_t value)
{
  servo_status_t status = SERVO_ERROR;
  if (value > MAX)
  {
    status = SERVO_OUT_OF_RANGE;
    value = MAX;
  }
  else if (value < MIN)
  {
    status = SERVO_OUT_OF_RANGE;
    value = MIN;
  }
  else
  {
    status = SERVO_OK;
  }
  printf("Setting servo gpio: %d\n", value);
  m_gpio_value = value;
  pwmWrite(SERVO_PIN, value);

  return status;
}

Servo::servo_status_t Servo::setAngle(int16_t angle)
{
  return setGpioRegister(angleToGpioValue(angle));
}

int Servo::angleToGpioValue(int16_t angle) const
{
  return ZERO + angle;
}

int16_t Servo::gpioValueToAngle(int value) const
{
  return value - ZERO;
}

Servo::servo_status_t Servo::StepLeft()
{
  return setGpioRegister(m_gpio_value - 10);
}

Servo::servo_status_t Servo::StepRight()
{
  return setGpioRegister(m_gpio_value + 10);
}

const char* Servo::getStatusText(servo_status_t status) const
{
  return error_values[status];
}


