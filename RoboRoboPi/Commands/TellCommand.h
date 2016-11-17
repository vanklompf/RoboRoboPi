#ifndef TELL_COMMAND_H
#define TELL_COMMAND_H

#include "commands/ICommand.h"
#include <string>

namespace robo
{
  class ISpeechSynthesizer;

  class TellCommand final : public ICommand
  {
  public:
    TellCommand(ISpeechSynthesizer& synthesizer);
    const std::string operator()(const std::string& command);
    const std::string GetHelp() const;
  private:
    ISpeechSynthesizer& m_synthesizer;
  };
}

#endif /* TELL_COMMAND_H */