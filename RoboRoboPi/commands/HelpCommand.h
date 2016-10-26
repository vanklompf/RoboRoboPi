#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include "commands/ICommand.h"
#include "MessageHandler.h"
#include <string>

namespace robo
{
  class HelpCommand final : public ICommand
  {
  public:
    HelpCommand(const CommandsMap& commands);
    const std::string operator()(const std::string& command);
    const std::string GetHelp() const;
  private:
    const CommandsMap& m_commands;
  };
}

#endif /* HELP_COMMAND_H */