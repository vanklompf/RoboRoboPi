#include "ConnectionListener.h"

#include "gloox\src\client.h"
#include "logger.h"

namespace robo
{
  ConnectionListener::ConnectionListener(gloox::Client& client): m_client(client){}

  void ConnectionListener::onConnect()
  {
    LogDebug("Client %s connected", m_client.jid().bare().c_str());
  }

  void ConnectionListener::onDisconnect(gloox::ConnectionError e)
  {
    switch(e)
    {
    case gloox::ConnAuthenticationFailed:
      LogDebug("auth failed. reason: %d", m_client.authError());
      break;
    case gloox::ConnStreamError:
      LogDebug("Stream error. Reason: %s", m_client.streamErrorText().c_str());
      break;
    case gloox::ConnIoError:
      LogDebug("IO error");
      break;
    default:
      LogDebug("Other error: %d", e);
      break;
    }
  }
}