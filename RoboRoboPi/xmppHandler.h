#ifndef XMPP_HANDLER_H
#define XMPP_HANDLER_H

#include "messagehandler.h"
#include "connectionlistener.h"
#include "gloox.h"

namespace gloox
{
  class Client;
  class Message;
  class MessageSession;
  struct CertInfo;
}
class Servo;

class RoboXmpp : public gloox::MessageHandler, gloox::ConnectionListener
{
private:
  gloox::Client* m_client;
  Servo& m_servo;

public:
  RoboXmpp(Servo& servo);
  ~RoboXmpp();

  // MessageHandler
  virtual void handleMessage(const gloox::Message& stanza, gloox::MessageSession* session = 0);

  // ConnectionListener
  virtual bool onTLSConnect(const gloox::CertInfo& info) { return true; }
  virtual void onConnect();
  virtual void onDisconnect(gloox::ConnectionError e);
};

#endif /* XMPP_HANDLER_H */