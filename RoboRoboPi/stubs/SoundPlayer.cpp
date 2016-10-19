#include "SoundPlayer.h"
#include <string>
#include <windows.h>
#include <mmsystem.h>

namespace robo
{
  bool PlaySoundFromFile(std::string sound)
  {
    std::string filename = "Sounds\\" + sound + ".wav";
    return PlaySound(filename.c_str(), NULL, SND_FILENAME | SND_NODEFAULT) != 0;
  }
}