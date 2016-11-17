#include "SpeechSynthesizerTts.h"
#include "logger.h"
#include "picotts/TtsEngine.h"
#include "ISoundPlayer.h"

#include <iterator>
#include <functional>
using namespace android;
namespace robo
{
  SpeechSynthesizerTts::SpeechSynthesizerTts(const ISoundPlayer& soundPlayer) : m_soundPlayer(soundPlayer)
  {
  }

  tts_callback_status SpeechSynthesizerTts::SynthDoneAlsa(void*& userdata, uint32_t sample_rate,
    tts_audio_format audio_format, int channels, int8_t*& data, size_t& size, tts_synth_status status)
  {
    if ((size == OUTPUT_BUFFER_SIZE) || (status == TTS_SYNTH_DONE))
    {
      LogDebug("Copy data: %d\n", size);
      s_buffer.insert(s_buffer.end(), data, data+size);
    }

    if (status == TTS_SYNTH_DONE)
    {
      s_synthesisComplete = true;
    }

    return TTS_CALLBACK_CONTINUE;
  }

  SpeechSynthesizerTts::~SpeechSynthesizerTts()
  {
  }

  bool SpeechSynthesizerTts::Say(std::string phrase)
  {
    LogDebug("Synthesising text... %s \n", phrase.c_str());
    auto synthBuffer = new int8_t[OUTPUT_BUFFER_SIZE];

    s_synthesisComplete = false;
    if (m_ttsEngine->synthesizeText(phrase.c_str(), synthBuffer, OUTPUT_BUFFER_SIZE, NULL) != TTS_SUCCESS)
    {
      LogDebug("Failed to synth text\n");
    }

    //Todo: use semaphore
    while (!synthesis_complete)
    {
      usleep(100);
    }

    m_soundPlayer.PlayPcm(s_buffer.data(), OUTPUT_BUFFER_SIZE);

    delete[] synthBuffer;
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
      LogDebug("Failed to load language\n");
    }
  }
}
