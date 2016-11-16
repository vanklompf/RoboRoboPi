#ifndef SPEECH_SYNTHESIZER_H
#define SPEECH_SYNTHESIZER_H
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
  class AlsaPcmPlayer;

  class SpeechSynthesizerTts : ISpeechSynthesizer
  {
  public:
    SpeechSynthesizerTts(const AlsaPcmPlayer& alsaPcmPlayer);
    void Init();
    bool Say(std::string phrase);
    ~SpeechSynthesizerTts();
  private:
    static android::tts_callback_status SynthDoneAlsa(void*& userdata, uint32_t sample_rate,
      android::tts_audio_format audio_format, int channels, int8_t*& data, size_t& size, android::tts_synth_status status);

    const AlsaPcmPlayer& m_pcmPlayer;
    android::TtsEngine* m_ttsEngine;
    static std::vector<int8_t> s_buffer;
    static bool s_synthesisComplete;

  };
}

#endif /* SPEECH_SYNTHESIZER_H */