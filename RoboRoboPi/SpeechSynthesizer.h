#ifndef SPEECH_SYNTHESIZER_H
#define SPEECH_SYNTHESIZER_H
#include <string>

namespace android
{
  class TtsEngine;
}

namespace robo
{
  class AlsaPcmPlayer;

  class SpeechSynthesizer
  {
  public:
    SpeechSynthesizer(const AlsaPcmPlayer& alsaPcmPlayer);
    void Init();
    bool Say(std::string phrase);
    ~SpeechSynthesizer();
  private:
    const AlsaPcmPlayer& m_pcmPlayer;
    android::TtsEngine* m_ttsEngine;
  };
}

#endif /* SPEECH_SYNTHESIZER_H */