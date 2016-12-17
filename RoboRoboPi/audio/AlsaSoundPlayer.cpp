#include "audio/AlsaSoundPlayer.h"
#include "logger.h"
#include <alsa/asoundlib.h>
#include <sndfile.h>
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
    unsigned int pcm;
    unsigned int rate = 16000;

    if ((pcm = snd_pcm_open(&m_pcmHandle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
      LogDebug("ERROR: Can't open \"%s\" PCM device. %s\n", "default", snd_strerror(pcm));
    }
    snd_pcm_hw_params_alloca(&m_hwParams);
    snd_pcm_hw_params_any(m_pcmHandle, m_hwParams);

    if ((pcm = snd_pcm_hw_params_set_access(m_pcmHandle, m_hwParams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
      LogDebug("ERROR: Can't set non interleaved mode. %s\n", snd_strerror(pcm));
      return;
    }
    if ((pcm = snd_pcm_hw_params_set_format(m_pcmHandle, m_hwParams, SND_PCM_FORMAT_S16_LE)) < 0)
    {
      LogDebug("ERROR: Can't set format. %s\n", snd_strerror(pcm));
      return;
    }

    if ((pcm = snd_pcm_hw_params_set_channels(m_pcmHandle, m_hwParams, 1)) < 0)
    {
      LogDebug("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));
      return;
    }

    LogDebug("Setting rate: %d", rate);
    if ((pcm = snd_pcm_hw_params_set_rate_near(m_pcmHandle, m_hwParams, &rate, 0)) < 0)
    {
      LogDebug("ERROR: Can't set rate. %s\n", snd_strerror(pcm));
      return;
    }

    if ((pcm = snd_pcm_hw_params(m_pcmHandle, m_hwParams)) < 0)
    {
      LogDebug("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));
      return;
    }

    snd_pcm_hw_params_get_period_size(m_hwParams, &m_frames, 0);

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

  bool AlsaSoundPlayer::PlayWav(const std::string& file) const
  {
    SF_INFO sfinfo;
    SNDFILE *infile = sf_open(file.c_str(), SFM_READ, &sfinfo);
    LogDebug("Channels: %d", sfinfo.channels);
    LogDebug("Sample rate: %d", sfinfo.samplerate);
    LogDebug("Sections: %d", sfinfo.sections);
    LogDebug("Format: %d", sfinfo.format);

    unsigned int pcm;
    if ((pcm = snd_pcm_hw_params_set_rate_near(m_pcmHandle, m_hwParams, &(unsigned int)sfinfo.samplerate, 0)) < 0)
    {
      LogDebug("ERROR: Can't set rate. %s\n", snd_strerror(pcm));
      return;
    }

    auto buf = new int16_t[m_frames * sfinfo.channels];
    sf_count_t readcount;
    while ((readcount = sf_readf_short(infile, buf, m_frames)) > 0) 
    {
      LogDebug("readcount: %d", readcount);
      auto pcm = snd_pcm_writei(m_pcmHandle, buf, readcount);
      if (pcm == -EPIPE)
      {
        LogDebug("Underrun!");
        snd_pcm_prepare(m_pcmHandle);
        sf_close(infile);
        return false;
      }
      else if (pcm < 0)
      {
        LogDebug("Error writing to PCM device: %s\n", snd_strerror(pcm));
        snd_pcm_prepare(m_pcmHandle);
        sf_close(infile);
        return false;
      }
      else if (pcm != readcount)
      {
        LogDebug("PCM write differs from PCM read.\n");
        snd_pcm_prepare(m_pcmHandle);
        sf_close(infile);
        return false;
      }
    }
    delete[] buf;
    sf_close(infile);
    return true;
  }
}