#include "SpeechSynthesizer.h"
#include "logger.h"
#include "picotts/TtsEngine.h"
#include <alsa/asoundlib.h>

using namespace android;
namespace robo
{
  #define OUTPUT_BUFFER_SIZE (128 * 1024)

  struct alsa_params {
    char *alsa_buff;
    int buffer_size;
    snd_pcm_uframes_t frames;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *hw_params;
  };

  struct alsa_params alsa_glob;
  static bool synthesis_complete = false;


  static tts_callback_status synth_done_alsa(void *& userdata, uint32_t sample_rate,
    tts_audio_format audio_format, int channels, int8_t *& data, size_t& size, tts_synth_status status)
  {
    LogDebug("synth_done_alsa. size: %d status: %d", size, status);

    if ((size == OUTPUT_BUFFER_SIZE) || (status == TTS_SYNTH_DONE))
    {
      LogDebug("Copy buffer\n");
      size_t old_buf_size = alsa_glob.buffer_size;
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

  void SpeechSynthesizer::Init()
  {
    AlsaInit();
    TtsInit();
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

    char* buff = alsa_glob.alsa_buff;
    unsigned int data_remaining = alsa_glob.buffer_size;
    int pcm;

    while (data_remaining > 0) 
    {
      snd_pcm_uframes_t remaining_frames = data_remaining > (alsa_glob.frames * 2) ? alsa_glob.frames : data_remaining / 2;
      printf("data_remaining: %d. remaining_frames: %ld\n", data_remaining, remaining_frames);
      
      pcm = snd_pcm_writei(alsa_glob.pcm_handle, buff, remaining_frames);
      if (pcm == -EPIPE)
      {
        snd_pcm_prepare(alsa_glob.pcm_handle);
      }
      else if (pcm < 0) 
      {
        LogDebug("ERROR. Can't write to PCM device. %s\n", snd_strerror(pcm));
        break;
      }

      data_remaining -= alsa_glob.frames * 2;
      buff += alsa_glob.frames * 2;
    }

    snd_pcm_drain(alsa_glob.pcm_handle);
    snd_pcm_close(alsa_glob.pcm_handle);
    delete[] synthBuffer;
    alsa_glob.buffer_size = 0;

    return true;
  }

  void SpeechSynthesizer::TtsInit()
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

  bool SpeechSynthesizer::AlsaInit()
  {
    LogDebug("Initializing Alsa...");
    unsigned int pcm;
    unsigned int rate;
    alsa_glob.buffer_size = 0;
    alsa_glob.alsa_buff = (char*)malloc(OUTPUT_BUFFER_SIZE / 2);
    rate = 16000;

    if ((pcm = snd_pcm_open(&alsa_glob.pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
      LogDebug("ERROR: Can't open \"%s\" PCM device. %s\n", "default", snd_strerror(pcm));
    }
    snd_pcm_hw_params_alloca(&alsa_glob.hw_params);
    snd_pcm_hw_params_any(alsa_glob.pcm_handle, alsa_glob.hw_params);

    if ((pcm = snd_pcm_hw_params_set_access(alsa_glob.pcm_handle, alsa_glob.hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) 
    {
      LogDebug("ERROR: Can't set non interleaved mode. %s\n", snd_strerror(pcm));
      return false;
    }
    if ((pcm = snd_pcm_hw_params_set_format(alsa_glob.pcm_handle, alsa_glob.hw_params, SND_PCM_FORMAT_S16_LE)) < 0) 
    {
      LogDebug("ERROR: Can't set format. %s\n", snd_strerror(pcm));
      return false;
    }

    if ((pcm = snd_pcm_hw_params_set_channels(alsa_glob.pcm_handle, alsa_glob.hw_params, 1)) < 0) 
    {
      LogDebug("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));
      return false;
    }

    if ((pcm = snd_pcm_hw_params_set_rate_near(alsa_glob.pcm_handle, alsa_glob.hw_params, &rate, 0)) < 0) 
    {
      LogDebug("ERROR: Can't set rate. %s\n", snd_strerror(pcm));
      return false;
    }

    if ((pcm = snd_pcm_hw_params(alsa_glob.pcm_handle, alsa_glob.hw_params)) < 0) 
    {
      LogDebug("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));
      return false;
    }

    snd_pcm_hw_params_get_period_size(alsa_glob.hw_params, &alsa_glob.frames, 0);

    alsa_glob.buffer_size = alsa_glob.frames * /*channels*/ 1 * /*sample_size*/ 2;

    if ((pcm = snd_pcm_prepare(alsa_glob.pcm_handle)) < 0)
    {
      LogDebug("cannot prepare audio interface for use (%s)\n", snd_strerror(pcm));
      exit(1);
    }
    return true;
  }
}
