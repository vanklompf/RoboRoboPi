#ifndef SPEECH_SYNTHESIZER_H
#define SPEECH_SYNTHESIZER_H
#include <string>

namespace android
{
  class TtsEngine;
}


namespace robo
{
  class SpeechSynthesizer
  {
  public:
    void Init();
    bool Say(std::string phrase);
    ~SpeechSynthesizer();
  private:
    bool AlsaInit();
    void TtsInit();
    android::TtsEngine* m_ttsEngine;
  };

}

#endif /* SPEECH_SYNTHESIZER_H */