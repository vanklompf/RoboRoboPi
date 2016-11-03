#ifndef SPEECH_SYNTHESIZER_H
#define SPEECH_SYNTHESIZER_H
#include <string>


namespace robo
{
  class SpeechSynthesizer
  {
  public:
    void Init();
    bool Say(std::string phrase);
  };

}

#endif /* SPEECH_SYNTHESIZER_H */