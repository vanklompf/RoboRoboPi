#include "TellCommand.h"
#include "logger.h"
#include "SpeechSynthesizer.h"
#include <string>

namespace robo
{
  const std::string TellCommand::operator()(const std::string& command)
  {
    LogDebug("Executing SpeakCommand(\"%s\")", command.c_str());
    int status = Say(command);

    if (status == 0)
    {
      return "OK";
    }
    else
    {
      return "System error: " + std::to_string(status);
    }
  }

  const std::string TellCommand::GetHelp() const
  {
    return
      "Tell\n"
      "Parameter: <words to be spoken>\n"
      ;
  }
}
