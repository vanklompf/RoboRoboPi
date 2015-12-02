#include "client.h"
#include "messagehandler.h"
#include "message.h"
#include "xmppHandler.h"
#include "servo.h"

#include <string>
using namespace gloox;

RoboXmpp::RoboXmpp(Servo& servo) : m_servo(servo)
{
  JID jid("robo@xmppeval.cloudapp.net");
  m_client = new Client(jid, "abcd");

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
  Servo::servo_status_t status = Servo::SERVO_ERROR;

  if (!stanza.body().empty())
  {
    char command = stanza.body().front();

    if ((command <= '9') && (command >= '0'))
    {
      int value = ((command - '0') * 10) - 42;
      status = m_servo.setAngle(value);
    }
    else
    {
      switch (command)
      {
      case 'l':
        status = m_servo.StepLeft();
        break;
      case 'r':
        status = m_servo.StepRight();
        break;
      default:
        status = Servo::SERVO_ERROR;
        break;
      }
    }
  }

  Message msg(Message::Chat, stanza.from(), m_servo.getStatusText(status));
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