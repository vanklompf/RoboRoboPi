#ifndef CONNECTION_LISTENER_H
#define CONNECTION_LISTENER_H

#include "gloox/src/gloox.h"
#include "gloox/src/connectionlistener.h"

namespace gloox
{
  class Client;
}

namespace robo
{
  class ConnectionListener final : public gloox::ConnectionListener
  {
  public:
    ConnectionListener(gloox::Client& client);

  protected:
    void onConnect();
    void onDisconnect(gloox::ConnectionError e);
    bool onTLSConnect(const gloox::CertInfo& info) { return true; }

  private:
    gloox::Client& m_client;
  };
}

#endif /* CONNECTION_LISTENER_H */