#ifndef SPEECH_SYNTHESIZER_PS_H
#define SPEECH_SYNTHESIZER_PS_H
#include <ISpeechSynthesizer.h>
#include <string>
#include <vector>
#include "picotts/TtsEngine.h"

namespace android
{
  class TtsEngine;
}

namespace robo
{
  class SpeechSynthesizerPs : public ISpeechSynthesizer
  {
  public:
    void Init() {};
    bool Say(std::string phrase);
  };
}

#endif /* SPEECH_SYNTHESIZER_PS_H */