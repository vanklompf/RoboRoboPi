#include "HelpCommand.h"
#include "logger.h"
#include "MessageHandler.h"
#include <string>
#include <sstream>

namespace robo
{
  HelpCommand::HelpCommand(const CommandsMap& commands) : m_commands(commands)
  {
  }

  const std::string HelpCommand::operator()(const std::string& command)
  {
    LogDebug("Executing HelpCommand(\"%s\")", command.c_str());
    std::stringstream ss;
    ss << "Available commands:" << std::endl;

    for (auto const &cmd : m_commands)
    {
      ss << cmd.first << std::endl;
      ss << cmd.second->GetHelp();
      ss << "----------------------" << std::endl;
    }

    return ss.str();
  }

  const std::string HelpCommand::GetHelp() const
  {
    return "Shows help for all available commands.\n";
  }
}


