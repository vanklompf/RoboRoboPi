#ifndef ISPEECH_SYNTHESIZER_H
#define ISPEECH_SYNTHESIZER_H
#include <string>

namespace robo
{

  class ISpeechSynthesizer
  {
  public:
    virtual void Init() = 0;
    virtual bool Say(std::string phrase) = 0;
  };
}

#endif /* ISPEECH_SYNTHESIZER_H */
