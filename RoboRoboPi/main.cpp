#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include "servo.h"

#include "xmppHandler.h"
using namespace std::literals;

void blink()
{
    while(1)
    {
        digitalWrite (16, HIGH);
        std::this_thread::sleep_for(500ms);
        digitalWrite (16,  LOW);
        std::this_thread::sleep_for(500ms);
    }
}

int main(void)
{
    wiringPiSetup();
    
    pinMode (16, OUTPUT);

    std::thread t1(blink);
    Servo servo;
    servo.init();
    RoboXmpp robo(servo);


    while(1)
    {
        int16_t angle;
        scanf("%hi", &angle);
        servo.setAngle(angle);
    }
}