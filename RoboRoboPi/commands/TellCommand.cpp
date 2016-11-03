#include "commands/TellCommand.h"
#include "logger.h"
#include "SpeechSynthesizer.h"
#include <string>

namespace robo
{
  TellCommand::TellCommand(SpeechSynthesizer& synthesizer) : m_synthesizer(synthesizer)
  {
  }

  const std::string TellCommand::operator()(const std::string& command)
  {
    LogDebug("Executing SpeakCommand(\"%s\")", command.c_str());

    if (m_synthesizer.Say(command))
    {
      return "OK";
    }
    else
    {
      return "System error";
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
