#include "AlsaSoundPlayer.h"
#include "logger.h"
#include <alsa/asoundlib.h>
#include <algorithm>
#include <vector>

namespace robo
{
  AlsaSoundPlayer::~AlsaSoundPlayer()
  {
    snd_pcm_drain(m_pcmHandle);
    snd_pcm_close(m_pcmHandle);
  }

  void AlsaSoundPlayer::Init()
  {
    LogDebug("Initializing Alsa...");
    snd_pcm_hw_params_t* hwParams;
    unsigned int pcm;
    unsigned int rate = 16000;

    if ((pcm = snd_pcm_open(&m_pcmHandle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
      LogDebug("ERROR: Can't open \"%s\" PCM device. %s\n", "default", snd_strerror(pcm));
    }
    snd_pcm_hw_params_alloca(&hwParams);
    snd_pcm_hw_params_any(m_pcmHandle, hwParams);

    if ((pcm = snd_pcm_hw_params_set_access(m_pcmHandle, hwParams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
      LogDebug("ERROR: Can't set non interleaved mode. %s\n", snd_strerror(pcm));
      return;
    }
    if ((pcm = snd_pcm_hw_params_set_format(m_pcmHandle, hwParams, SND_PCM_FORMAT_S16_LE)) < 0)
    {
      LogDebug("ERROR: Can't set format. %s\n", snd_strerror(pcm));
      return;
    }

    if ((pcm = snd_pcm_hw_params_set_channels(m_pcmHandle, hwParams, 1)) < 0)
    {
      LogDebug("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));
      return;
    }

    if ((pcm = snd_pcm_hw_params_set_rate_near(m_pcmHandle, hwParams, &rate, 0)) < 0)
    {
      LogDebug("ERROR: Can't set rate. %s\n", snd_strerror(pcm));
      return;
    }

    if ((pcm = snd_pcm_hw_params(m_pcmHandle, hwParams)) < 0)
    {
      LogDebug("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));
      return;
    }

    snd_pcm_hw_params_get_period_size(hwParams, &m_frames, 0);

    LogDebug("alsa_glob.frames: %d", m_frames);

    if ((pcm = snd_pcm_prepare(m_pcmHandle)) < 0)
    {
      LogDebug("cannot prepare audio interface for use (%s)\n", snd_strerror(pcm));
    }
  }

  void AlsaSoundPlayer::PlayPcm(const std::vector<int8_t>& buf) const
  {
    auto pos = buf.begin();

    while (pos != buf.end())
    {
      auto remaining_data = std::distance(pos, buf.end());
      snd_pcm_uframes_t remaining_frames = (uint32_t)(remaining_data / 2) > m_frames ? m_frames : remaining_data / 2;
      //printf("data_remaining: %d. remaining_frames: %ld\n", remaining_data, remaining_frames);

      auto pcm = snd_pcm_writei(m_pcmHandle, &(*pos), remaining_frames);
      if (pcm == -EPIPE)
      {
        snd_pcm_prepare(m_pcmHandle);
      }
      else if (pcm < 0)
      {
        LogDebug("ERROR. Can't write to PCM device. %s\n", snd_strerror(pcm));
        break;
      }

      pos += remaining_frames * 2;
    }
  }
}