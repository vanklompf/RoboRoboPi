#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include "servo.h"

#include "xmppHandler.h"
#include "xmppComponent.h"
using namespace std::literals;

void blink()
{
    pinMode(16, OUTPUT);
    while(1)
    {
        digitalWrite (16, HIGH);
        std::this_thread::sleep_for(500ms);
        digitalWrite (16,  LOW);
        std::this_thread::sleep_for(500ms);
    }
}

void component()
{
  XmppComponent comp;
}

int main(void)
{
    wiringPiSetup();

    std::thread t1(blink);
    std::thread t2(component);
    Servo servo;
    servo.init();
    RoboXmpp robo(servo);
}