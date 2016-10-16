#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "gloox\src\messagehandler.h"
#include "gloox\src\gloox.h"
#include <memory>

namespace gloox
{
  class Client;
  class Message;
  class MessageSession;
}

namespace robo 
{
  class Servo;
  class ICommand;

  class MessageHandler final : public gloox::MessageHandler
  {
  public:
    MessageHandler(gloox::Client& client);
    void RegisterCommand(char opcode, std::unique_ptr<ICommand> command);

    // MessageHandler
    virtual void handleMessage(const gloox::Message& stanza, gloox::MessageSession* session = 0);

  private:
    gloox::Client& m_client;
    std::map<char, std::unique_ptr<ICommand>> m_commands;
  };
}
#endif /* MESSAGE_HANDLER_H */