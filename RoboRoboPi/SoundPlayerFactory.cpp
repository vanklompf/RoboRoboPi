#include "SoundPlayerFactory.h"
#include "ISoundPlayer.h"
#ifdef __linux__ 
#include "AlsaSoundPlayer.h"
#elif _WIN32
#include "NullSoundPlayer.h"
#endif

namespace robo
{
  ISoundPlayer * SoundPlayerFactory::Create()
  {
#ifdef __linux__ 
    return new AlsaSoundPlayer();
#elif _WIN32
    return new NullSoundPlayer();
#endif
  }

  std::unique_ptr<ISoundPlayer> SoundPlayerFactory::CreateUniquePointer()
  {
    return std::unique_ptr<ISoundPlayer>(Create());
  }
}
