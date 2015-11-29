#include <wiringPi.h>
#include <stdio.h>
#include "servo.h"
/*
 *  values from
 *  http://stackoverflow.com/questions/20081286/controlling-a-servo-with-raspberry-pi-using-the-hardware-pwm-with-wiringpi
 *  Clock: 384 Range: 30 - 115
 *  Clock: 500 Range: 25 - 80
 *  Clock: 400 Range: 29 - 111
 *  Clock: 250 Range: 46 - 178
 *  Clock: 200 Range: 57 - 223
 *  Clock: 100 Not working
 */
void servoSetup()
{
    pinMode (1, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(400);
    pwmSetRange(1000);
}

void setServoRotation(int16_t angle)
{
    printf("Setting: %d\n", angle);
    pwmWrite(1, angle);
}
