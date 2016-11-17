#ifndef ALSA_SOUND_PLAYER_H
#define ALSA_SOUND_PLAYER_H
#include "ISoundPlayer.h"
#include <alsa/asoundlib.h>
#include <stdint.h>

namespace robo
{
  class AlsaSoundPlayer : public ISoundPlayer
  {
  public:
    ~AlsaSoundPlayer();
    void Init();
    void PlayPcm(const int8_t* buf, size_t size) const;
  private:
    snd_pcm_uframes_t m_frames;
    snd_pcm_t* m_pcmHandle;
  };
}


#endif /* ALSA_SOUND_PLAYER_H */