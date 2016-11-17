#ifndef ISOUND_PLAYER_H
#define ISOUND_PLAYER_H
#include <stdint.h>
#include <cstddef>

namespace robo
{
  class ISoundPlayer
  {
  public:
    virtual void Init() = 0;
    virtual void PlayPcm(const int8_t* buf, size_t size) const = 0;
  };
}

#endif /*ISOUND_PLAYER_H*/