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
  class Servo;
  class SpeechSynthesizer;
  class ICommand;

  class RoboRobo final
  {
  public:
    RoboRobo(std::unique_ptr<Servo> servo, std::unique_ptr<SpeechSynthesizer> synthesizer, std::unique_ptr<gloox::Client> xmppClient);
    ~RoboRobo();
    void Init();

  private:
    std::unique_ptr<Servo> m_servo;
    std::unique_ptr<SpeechSynthesizer> m_synthesizer;
    std::unique_ptr<gloox::Client> m_client;
  };
}
#endif /* XMPP_HANDLER_H */