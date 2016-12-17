#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "gloox/src/messagehandler.h"
#include "gloox/src/gloox.h"
#include <memory>
#include <map>
#include "commands/ICommand.h"

namespace gloox
{
  class Client;
  class Message;
  class MessageSession;
}

namespace robo 
{
  class ICommand;

  typedef std::map<char, std::unique_ptr<ICommand>> CommandsMap;

  class MessageHandler final : public gloox::MessageHandler
  {
  public:
    MessageHandler(gloox::Client& client, std::unique_ptr<CommandsMap> commandsMap);
    void RegisterCommand(char opcode, std::unique_ptr<ICommand> command);
    void RegisterDefaultCommand(std::unique_ptr<ICommand> command);

    // MessageHandler
    virtual void handleMessage(const gloox::Message& stanza, gloox::MessageSession* session = 0);

  private:
    gloox::Client& m_client;
    std::unique_ptr<CommandsMap> m_commands;
    std::unique_ptr<ICommand> m_default_command;
  };
}
#endif /* MESSAGE_HANDLER_H */