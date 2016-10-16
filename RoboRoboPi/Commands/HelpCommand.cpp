#include "HelpCommand.h"
#include "logger.h"
#include <string>

namespace robo
{
  std::string HelpCommand::operator()(const std::string& command)
  {
    LogDebug("Executing HelpCommand(\"%s\")", command.c_str());
    return "\n"\
      "This is help message.\n"\
      "This is even more helpful.";
  }
}


