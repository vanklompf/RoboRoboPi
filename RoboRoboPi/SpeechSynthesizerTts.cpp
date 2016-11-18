#include "SpeechSynthesizerTts.h"
#include "logger.h"
#include "picotts/TtsEngine.h"
#include "ISoundPlayer.h"

#include <vector>
#include <chrono>
#include <thread>
using namespace android;
namespace robo
{
  bool SpeechSynthesizerTts::s_synthesisComplete = false;
  std::vector<int8_t> SpeechSynthesizerTts::s_buffer;

  SpeechSynthesizerTts::SpeechSynthesizerTts(const ISoundPlayer& soundPlayer) : m_soundPlayer(soundPlayer)
  {
  }

  tts_callback_status SpeechSynthesizerTts::SynthDoneAlsa(void*& userdata, uint32_t sample_rate,
    tts_audio_format audio_format, int channels, int8_t*& data, size_t& size, tts_synth_status status)
  {
    if (status != TTS_SYNTH_DONE)
    {
      LogDebug("Copy data: %d", size);
      s_buffer.insert(s_buffer.end(), data, data+size);
    }
    else
    {
      s_synthesisComplete = true;
    }

    return TTS_CALLBACK_CONTINUE;
  }

  bool SpeechSynthesizerTts::Say(std::string phrase)
  {
    LogDebug("Synthesising text: <%s>", phrase.c_str());
    std::vector<int8_t> synthBuffer;
    synthBuffer.resize(128*1024);

    s_synthesisComplete = false;
    if (m_ttsEngine->synthesizeText(phrase.c_str(), synthBuffer.data(), synthBuffer.size(), NULL) != TTS_SUCCESS)
    {
      LogDebug("Failed to synth text");
    }

    //Todo: use semaphore
    while (!s_synthesisComplete)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    m_soundPlayer.PlayPcm(s_buffer);
    s_buffer.clear();
    return true;
  }

  void SpeechSynthesizerTts::Init()
  {
    LogDebug("Initializing PicoTts...");
    m_ttsEngine = android::getTtsEngine();

    if (m_ttsEngine->init(SynthDoneAlsa, "../picotts/") != TTS_SUCCESS)
    {
      LogDebug("Failed to init TTS\n");
    }

    auto lang = "eng";
    LogDebug("Setting language: %s", lang);
    if (m_ttsEngine->setLanguage(lang, "", ""))
    {
      LogDebug("Failed to load language");
    }
  }
}
