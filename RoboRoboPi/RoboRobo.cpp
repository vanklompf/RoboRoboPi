#include "RoboRobo.h"

#include "gloox/src/client.h"
#include "gloox/src/messagehandler.h"
#include "gloox/src/message.h"

#include "servo.h"
#include "audio/ISoundPlayer.h"
#include "audio/ISpeechSynthesizer.h"

#include <string>
#include <memory>
#include "logger.h"

namespace robo
{
  RoboRobo::RoboRobo(std::unique_ptr<Servo> servo, std::unique_ptr<ISoundPlayer> pcmPlayer, std::unique_ptr<ISpeechSynthesizer> synthesizer, std::unique_ptr<gloox::Client> xmppClient)
    : m_servo(std::move(servo)),
      m_soundPlayer(std::move(pcmPlayer)),
      m_synthesizer(std::move(synthesizer)),
      m_client(std::move(xmppClient))
  {
  }

  RoboRobo::~RoboRobo()
  {
    m_client->disconnect();
  }

  void RoboRobo::Init()
  {
    m_servo->Init();
    m_soundPlayer->Init();
    m_synthesizer->Init();
    m_client->connect();
  }
}