#include "gloox/src/client.h"
#include "gloox/src/messagehandler.h"
#include "gloox/src/message.h"

#include "RoboRobo.h"
#include "servo.h"

#include <string>
#include <memory>
#include "logger.h"

namespace robo
{
  RoboRobo::RoboRobo(std::unique_ptr<Servo> servo, std::unique_ptr<gloox::Client> xmppClient) 
    : m_servo(std::move(servo)), 
      m_client(std::move(xmppClient))
  {
  }

  RoboRobo::~RoboRobo()
  {
    m_client->disconnect();
  }

  void RoboRobo::Init()
  {
    //m_servo->init();
    m_client->connect();
  }
}