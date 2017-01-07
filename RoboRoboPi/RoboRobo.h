#ifndef XMPP_HANDLER_H
#define XMPP_HANDLER_H
#include "gloox/src/messagehandler.h"
#include "gloox/src/connectionlistener.h"
#include "gloox/src/gloox.h"
#include <memory>
#include <map>

namespace gloox
{
  class Client;
}

namespace robo
{
  class IGpio;
  class Servo;
  class ISpeechSynthesizer;
  class ICommand;
  class ISoundPlayer;

  class RoboRobo final
  {
  public:
    RoboRobo(std::unique_ptr<IGpio> gpio, std::unique_ptr<Servo> servo, std::unique_ptr<ISoundPlayer> pcmPlayer, std::unique_ptr<ISpeechSynthesizer> synthesizer, std::unique_ptr<gloox::Client> xmppClient);
    ~RoboRobo();
    void Init();

  private:
    void Blink();

    std::unique_ptr<IGpio> m_gpio;
    std::unique_ptr<Servo> m_servo;
    std::unique_ptr<ISoundPlayer> m_soundPlayer;
    std::unique_ptr<ISpeechSynthesizer> m_synthesizer;
    std::unique_ptr<gloox::Client> m_client;
  };
}
#endif /* XMPP_HANDLER_H */