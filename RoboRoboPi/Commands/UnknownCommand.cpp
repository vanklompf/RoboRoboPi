#include "UnknownCommand.h"
#include "logger.h"
#include <string>

namespace robo
{
  std::string UnknownCommand::operator()(const std::string& command)
  {
    LogDebug("Executing UnknownCommand(\"%s\")", command.c_str());
    return "Unknown command";
  }
}
