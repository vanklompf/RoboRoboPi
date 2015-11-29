#include <iostream>
#include <thread>
#include <wiringPi.h>
#include "servo.h"

void blink()
{
    while(1)
    {
        digitalWrite (16, HIGH);
        delay (500);
        digitalWrite (16,  LOW);
        delay (500);
    }
}

int main(void)
{
    wiringPiSetup();
    servoSetup();
    pinMode (16, OUTPUT);

    std::thread t1(blink);

    while(1)
    {
        int16_t angle;
        scanf("%i", &angle);
        setServoRotation(angle);
    }
}