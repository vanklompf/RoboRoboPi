#include "xmppComponent.h"
#include "gloox/src/component.h"
#include "logger.h"

namespace robo
{
  XmppComponent::XmppComponent()
  {
    m_component = new gloox::Component("jabber:component:accept", "xmppeval.cloudapp.net", "astro", "compabcd", 8888);
    m_component->registerConnectionListener(this);

    m_component->connect();
  }

  XmppComponent::~XmppComponent()
  {
    m_component->disconnect();
    delete m_component;
  }

  void XmppComponent::onConnect()
  {
    LogDebug("Client %s connected", m_component->jid().bare().c_str());
  }

  void XmppComponent::onDisconnect(gloox::ConnectionError e)
  {
    switch (e)
    {
    case gloox::ConnAuthenticationFailed:
      LogDebug("auth failed. reason: %d", m_component->authError());
      break;
    case gloox::ConnStreamError:
      LogDebug("Stream error. Reason: %s", m_component->streamErrorText().c_str());
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