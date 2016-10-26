#include "SoundPlayer.h"
#include "logger.h"
#include <string>
#include <cstdlib>

namespace robo
{
  bool PlaySoundFromFile(std::string soundFilePath)
  {
    return std::system(("omxplayer " + soundFilePath).c_str()) == 0;
  }
}