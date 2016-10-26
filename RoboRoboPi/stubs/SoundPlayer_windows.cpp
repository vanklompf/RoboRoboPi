#include "SoundPlayer.h"
#include <string>
#include <windows.h>
#include <mmsystem.h>

namespace robo
{
  bool PlaySoundFromFile(std::string soundFilePath)
  {
    return PlaySound(soundFilePath.c_str(), NULL, SND_FILENAME | SND_NODEFAULT) != 0;
  }
}