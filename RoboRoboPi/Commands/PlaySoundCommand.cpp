#include "PlaySoundCommand.h"
#include "logger.h"
#include "SoundPlayer.h"
#include <string>

namespace robo
{
  std::string PlaySoundCommand::operator()(const std::string& command)
  {
    LogDebug("Executing PlaySoundCommand(\"%s\")", command.c_str());
    return PlaySoundFromFile(command) ? "OK" : "Error playing sound";
  }
}
