#ifndef NULL_SOUND_PLAYER_H
#define NULL_SOUND_PLAYER_H
#include "audio/ISoundPlayer.h"
#include <stdint.h>
#include <vector>
#include <string>

namespace robo
{
  class WindowsSoundPlayer : public ISoundPlayer
  {
    void Init();
    void PlayPcm(const std::vector<int8_t>&) const {};
    bool PlayWav(const std::string&) const;
  };
}

#endif /* NULL_SOUND_PLAYER_H */