#ifndef SPEECH_SYNTHESIZER_TTS_H
#define SPEECH_SYNTHESIZER_TTS_H
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
  class ISoundPlayer;

  class SpeechSynthesizerTts : public ISpeechSynthesizer
  {
  public:
    SpeechSynthesizerTts(const ISoundPlayer& soundPlayer);
    void Init();
    bool Say(std::string phrase);
  private:
    static android::tts_callback_status SynthDoneAlsa(void*& userdata, uint32_t sample_rate,
      android::tts_audio_format audio_format, int channels, int8_t*& data, size_t& size, android::tts_synth_status status);

    const ISoundPlayer& m_soundPlayer;
    android::TtsEngine* m_ttsEngine;
    static std::vector<int8_t> s_buffer;
    static bool s_synthesisComplete;

  };
}

#endif /* SPEECH_SYNTHESIZER_TTS_H */