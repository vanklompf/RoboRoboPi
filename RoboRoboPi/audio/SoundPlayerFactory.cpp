#include "audio/SoundPlayerFactory.h"
#include "audio/ISoundPlayer.h"
#ifdef __linux__ 
#include "audio/AlsaSoundPlayer.h"
#elif _WIN32
#include "audio/WindowsSoundPlayer.h"
#endif

namespace robo
{
  ISoundPlayer * SoundPlayerFactory::Create()
  {
#ifdef __linux__ 
    return new AlsaSoundPlayer();
#elif _WIN32
    return new WindowsSoundPlayer();
#endif
  }

  std::unique_ptr<ISoundPlayer> SoundPlayerFactory::CreateUniquePointer()
  {
    return std::unique_ptr<ISoundPlayer>(Create());
  }
}
