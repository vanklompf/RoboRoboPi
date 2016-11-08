#include "RoboRobo.h"

#include "gloox/src/client.h"
#include "gloox/src/messagehandler.h"
#include "gloox/src/message.h"

#include "servo.h"
#include "AlsaPcmPlayer.h"
#include "SpeechSynthesizer.h"

#include <string>
#include <memory>
#include "logger.h"

namespace robo
{
  RoboRobo::RoboRobo(std::unique_ptr<Servo> servo, std::unique_ptr<AlsaPcmPlayer> pcmPlayer, std::unique_ptr<SpeechSynthesizer> synthesizer, std::unique_ptr<gloox::Client> xmppClient)
    : m_servo(std::move(servo)),
      m_pcmPlayer(std::move(pcmPlayer)),
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
    m_pcmPlayer->Init();
    m_synthesizer->Init();
    m_client->connect();
  }
}