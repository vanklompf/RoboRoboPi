#ifndef NULL_SOUND_PLAYER_H
#define NULL_SOUND_PLAYER_H
#include "ISoundPlayer.h"
#include <stdint.h>

namespace robo
{
  class NullSoundPlayer : public ISoundPlayer
  {
    void Init() {};
    void PlayPcm(const int8_t*, size_t) const {};
  };
}

#endif /* NULL_SOUND_PLAYER_H */