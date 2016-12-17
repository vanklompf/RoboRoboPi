#include "WindowsSoundPlayer.h"
#include <windows.h>
#include <mmsystem.h>

namespace robo
{
  bool WindowsSoundPlayer::PlayWav(const std::string& soundFilePath) const
  {
    return PlaySound(soundFilePath.c_str(), NULL, SND_FILENAME | SND_NODEFAULT) != 0;
  }
}