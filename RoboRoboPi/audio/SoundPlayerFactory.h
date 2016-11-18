#ifndef SOUND_PLAYER_FACTORY_H
#define SOUND_PLAYER_FACTORY_H
#include <memory>

namespace robo
{
  class ISoundPlayer;

  class SoundPlayerFactory
  {
  public:
    static ISoundPlayer* Create();
    static std::unique_ptr<ISoundPlayer> CreateUniquePointer();
  };
}

#endif /* SOUND_PLAYER_FACTORY_H */