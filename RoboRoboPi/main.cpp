#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include <pigpio.h>

#include "RoboRobo.h"
#include "RoboRoboFactory.h"
#include "xmppComponent.h"
#include "logger.h"


using namespace std::literals;
using namespace robo;

static const char* logPath = "log.txt";

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

void exitHandler(void)
{
    CloseLogger();
}

int main(void)
{
    InitLogger(logPath);
    LogDebug("------------------------------");
    LogDebug("RoboRoboPi Started");
    atexit(exitHandler);

    //wiringPiSetup();
    gpioInitialise();

    std::thread t1(blink);
    std::thread t2(component);

    auto robo = RoboRoboFactory::Create();
    robo->Init();
}

