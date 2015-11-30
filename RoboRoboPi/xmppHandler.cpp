#include "client.h"
#include "messagehandler.h"
#include "message.h"
#include "xmppHandler.h"

using namespace gloox;

RoboXmpp::RoboXmpp()
{
  //JID jid("robo@xmppeval.cloudapp.net");
  JID jid("robo@city.gov");
  m_client = new Client(jid, "abcd");

  m_client->setServer("192.168.2.2");
  m_client->disableRoster();
  m_client->registerMessageHandler(this);
  m_client->registerConnectionListener(this);

  m_client->connect();
}

RoboXmpp::~RoboXmpp()
{
  m_client->disconnect();
  delete m_client;
}

void RoboXmpp::handleMessage(const Message& stanza, MessageSession* session)
{
  Message msg(Message::Chat, stanza.from(), "hello world");
  m_client->send(msg);
}

void RoboXmpp::onConnect()
{
  printf("Client %s connected\n", m_client->jid().bare().c_str());
}

void RoboXmpp::onDisconnect(ConnectionError e)
{
  switch (e)
  {
  case ConnAuthenticationFailed:
    printf("auth failed. reason: %d\n", m_client->authError());
    break;
  case ConnStreamError:
    printf("Stream error. Reason: %s\n", m_client->streamErrorText().c_str());
    break;
  case ConnIoError:
    printf("IO error\n");
    break;
  default:
    printf("Other error: %d\n", e);
    break;
  }
}