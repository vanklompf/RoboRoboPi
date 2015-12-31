#include "xmppComponent.h"
#include "component.h"

using namespace gloox;

XmppComponent::XmppComponent()
{
  m_component = new Component("jabber:component:accept", "xmppeval.cloudapp.net", "astro", "compabcd", 8888);
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
  printf("Client %s connected\n", m_component->jid().bare().c_str());
}

void XmppComponent::onDisconnect(ConnectionError e)
{
  switch (e)
  {
  case ConnAuthenticationFailed:
    printf("auth failed. reason: %d\n", m_component->authError());
    break;
  case ConnStreamError:
    printf("Stream error. Reason: %s\n", m_component->streamErrorText().c_str());
    break;
  case ConnIoError:
    printf("IO error\n");
    break;
  default:
    printf("Other error: %d\n", e);
    break;
  }
}