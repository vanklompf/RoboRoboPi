#ifndef XMPP_HANDLER_H
#define XMPP_HANDLER_H

#include "client.h"
#include "messagehandler.h"
#include "message.h"
#include "connectionlistener.h"
#include "gloox.h"

class RoboXmpp : public gloox::MessageHandler, gloox::ConnectionListener
{
private:
  gloox::Client* m_client;

public:
  RoboXmpp();
  ~RoboXmpp();

  // MessageHandler
  virtual void handleMessage(const gloox::Message& stanza, gloox::MessageSession* session = 0);

  // ConnectionListener
  virtual bool onTLSConnect(const gloox::CertInfo& info) { return true; }
  virtual void onConnect();
  virtual void onDisconnect(gloox::ConnectionError e);
};

#endif /* XMPP_HANDLER_H */