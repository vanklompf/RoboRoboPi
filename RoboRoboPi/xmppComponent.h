#ifndef XMPP_COMPONENT_H
#define XMPP_COMPONENT_H


#include "connectionlistener.h"
#include "gloox.h"

namespace gloox
{
  class Component;
}

class XmppComponent  : public gloox::ConnectionListener
{
public:
  XmppComponent();
  ~XmppComponent();

  gloox::ClientBase& GetClient() { return *m_component; }
private:
  // ConnectionListener
  virtual bool onTLSConnect(const gloox::CertInfo& info) { return true; }
  virtual void onConnect();
  virtual void onDisconnect(gloox::ConnectionError e);

  gloox::Component* m_component;
};

#endif /* XMPP_COMPONENT_H */