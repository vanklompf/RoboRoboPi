#include "RoboRobo.h"

#include "gloox/src/client.h"
#include "gloox/src/messagehandler.h"
#include "gloox/src/message.h"

#include "IGpio.h"
#include "Servo.h"
#include "audio/ISoundPlayer.h"
#include "audio/ISpeechSynthesizer.h"

#include <string>
#include <memory>
#include "logger.h"

#include <chrono>
#include <thread>


namespace robo
{
  using namespace std::chrono_literals;

  RoboRobo::RoboRobo(std::unique_ptr<IGpio> gpio, std::unique_ptr<Servo> servo, std::unique_ptr<ISoundPlayer> pcmPlayer, std::unique_ptr<ISpeechSynthesizer> synthesizer, std::unique_ptr<gloox::Client> xmppClient)
    : m_gpio(std::move(gpio)),
      m_servo(std::move(servo)),
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
    m_gpio->Init();
    m_servo->Init();
    m_soundPlayer->Init();
    m_synthesizer->Init();
    //std::thread t1(&RoboRobo::Blink, this);

    m_client->connect();
  }

  void RoboRobo::Blink()
  {
    LogDebug("Blink start");
    while (1)
    {
      m_gpio->LedOn(led_t::YELLOW_LED);
      m_gpio->LedOff(led_t::ORANGE_LED);
      std::this_thread::sleep_for(500ms);
      m_gpio->LedOff(led_t::YELLOW_LED);
      m_gpio->LedOn(led_t::ORANGE_LED);
      std::this_thread::sleep_for(500ms);
    }
  }
}