#include <csignal>

#include "RoboRobo.h"
#include "RoboRoboFactory.h"
#include "xmppComponent.h"
#include "logger.h"

using namespace robo;
using namespace std::literals;

  static const char* logPath = "log.txt";
  static RoboRobo* roboRobo;

  void exitHandler(void)
  {
    CloseLogger();
    delete roboRobo;
  }

  void signalHandler(int signum)
  {
    exit(0);
  }

  int main(void)
  {
    InitLogger(logPath);
    LogDebug("------------------------------");
    LogDebug("RoboRoboPi Started");
    atexit(exitHandler);
    signal(SIGTERM, signalHandler);

    roboRobo = RoboRoboFactory::Create();
    roboRobo->Init();

    return 0;
  }

