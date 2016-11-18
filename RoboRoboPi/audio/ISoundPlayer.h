#ifndef ISOUND_PLAYER_H
#define ISOUND_PLAYER_H
#include <stdint.h>
#include <vector>

namespace robo
{
  class ISoundPlayer
  {
  public:
    virtual void Init() = 0;
    virtual void PlayPcm(const std::vector<int8_t>& buf) const = 0;
  };
}

#endif /*ISOUND_PLAYER_H*/