#include "MessageHandler.h"

#include "gloox\src\client.h"
#include "gloox\src\messagehandler.h"
#include "gloox\src\message.h"

#include <cctype>
#include "logger.h"
#include "ICommand.h"

namespace robo
{
  MessageHandler::MessageHandler(gloox::Client& client) : m_client(client){}

  void MessageHandler::handleMessage(const gloox::Message& stanza, gloox::MessageSession* session)
  {
    std::string status = "Unknown Error";

    if (!stanza.body().empty())
    {
      LogDebug("Rcv msg from: <%s>. Body: <%s>", stanza.from().full().c_str(), stanza.body().c_str());
      char opcode = std::tolower(stanza.body().front());

      auto param = stanza.body().size() > 2 ? stanza.body().substr(2) : "";
      if (m_commands.find(opcode) != m_commands.end())
      {
        status = m_commands.at(opcode)->operator()(param);
      }
      else
      {
        status = m_default_command->operator()(param);
      }
    }
    else
    {
      status = "Empty command";
    }

    gloox::Message msg(gloox::Message::Chat, stanza.from(), status);
    LogDebug("Sending message: %s", msg.body().c_str());
    m_client.send(msg);
  }

  void MessageHandler::RegisterCommand(char opcode, std::unique_ptr<ICommand> command)
  {
    m_commands[opcode] = std::move(command);
  }

  void MessageHandler::RegisterDefaultCommand(std::unique_ptr<ICommand> command)
  {
    m_default_command = std::move(command);
  }
}