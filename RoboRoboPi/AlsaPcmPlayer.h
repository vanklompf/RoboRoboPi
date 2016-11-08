#ifndef SALSA_PCM_PLAYER_H
#define SALSA_PCM_PLAYER_H
#include <alsa/asoundlib.h>
#include <stdint.h>

namespace robo
{
  class AlsaPcmPlayer
  {
  public:
    ~AlsaPcmPlayer();
    void Init();
    void Play(const int8_t* buf, size_t size) const;
  private:
    snd_pcm_uframes_t m_frames;
    snd_pcm_t* m_pcmHandle;
  };
}


#endif /* SALSA_PCM_PLAYER_H */