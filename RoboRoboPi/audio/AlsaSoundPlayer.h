#ifndef ALSA_SOUND_PLAYER_H
#define ALSA_SOUND_PLAYER_H
#include "audio/ISoundPlayer.h"
#include <alsa/asoundlib.h>
#include <stdint.h>
#include <vector>

namespace robo
{
  class AlsaSoundPlayer : public ISoundPlayer
  {
  public:
    ~AlsaSoundPlayer();
    void Init();
    void PlayPcm(const std::vector<int8_t>& buf) const;
  private:
    snd_pcm_uframes_t m_frames;
    snd_pcm_t* m_pcmHandle;
  };
}


#endif /* ALSA_SOUND_PLAYER_H */