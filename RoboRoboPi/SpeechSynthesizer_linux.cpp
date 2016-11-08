#include "SpeechSynthesizer.h"
#include "logger.h"
#include "picotts/TtsEngine.h"

#include "AlsaPcmPlayer.h"

using namespace android;
namespace robo
{
  #define OUTPUT_BUFFER_SIZE (128 * 1024)
  static bool synthesis_complete = false;

  SpeechSynthesizer::SpeechSynthesizer(const AlsaPcmPlayer& alsaPcmPlayer) : m_pcmPlayer(alsaPcmPlayer)
  {
  }

  static tts_callback_status synth_done_alsa(void *& userdata, uint32_t sample_rate,
    tts_audio_format audio_format, int channels, int8_t *& data, size_t& size, tts_synth_status status)
  {
    if ((size == OUTPUT_BUFFER_SIZE) || (status == TTS_SYNTH_DONE))
    {
      size_t old_buf_size = alsa_glob.buffer_size;
      LogDebug("Copy data: %d. To buffer starting at: %d\n", size, old_buf_size);
      alsa_glob.buffer_size += size;
      alsa_glob.alsa_buff = (char*)realloc(alsa_glob.alsa_buff, alsa_glob.buffer_size);
      char* start = alsa_glob.alsa_buff + old_buf_size;
      memcpy(start, data, size);
    }

    if (status == TTS_SYNTH_DONE)
    {
      synthesis_complete = true;
    }

    return TTS_CALLBACK_CONTINUE;
  }

  SpeechSynthesizer::~SpeechSynthesizer()
  {
    free(alsa_glob.alsa_buff);
  }

  bool SpeechSynthesizer::Say(std::string phrase)
  {
    LogDebug("Synthesising text... %s \n", phrase.c_str());
    auto synthBuffer = new int8_t[OUTPUT_BUFFER_SIZE];

    if (m_ttsEngine->synthesizeText(phrase.c_str(), synthBuffer, OUTPUT_BUFFER_SIZE, NULL) != TTS_SUCCESS)
    {
      LogDebug("Failed to synth text\n");
    }

    //Todo: use semaphore
    while (!synthesis_complete)
    {
      usleep(100);
    }

    m_pcmPlayer.Play(synthBuffer, OUTPUT_BUFFER_SIZE);

    delete[] synthBuffer;
    return true;
  }

  void SpeechSynthesizer::Init()
  {
    LogDebug("Initializing PicoTts...");
    m_ttsEngine = android::getTtsEngine();
    if (m_ttsEngine->init(synth_done_alsa, "../picotts/") != TTS_SUCCESS)
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
