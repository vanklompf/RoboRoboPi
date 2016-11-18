#ifndef NULL_SOUND_PLAYER_H
#define NULL_SOUND_PLAYER_H
#include "audio/ISoundPlayer.h"
#include <stdint.h>
#include <vector>

namespace robo
{
  class NullSoundPlayer : public ISoundPlayer
  {
    void Init() {};
    void PlayPcm(const std::vector<int8_t>&) const {};
  };
}

#endif /* NULL_SOUND_PLAYER_H */