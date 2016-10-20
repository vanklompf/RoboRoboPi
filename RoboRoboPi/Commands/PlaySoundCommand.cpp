#include "PlaySoundCommand.h"
#include "logger.h"
#include "SoundPlayer.h"
#include <string>

namespace robo
{
  const std::string PlaySoundCommand::operator()(const std::string& command)
  {
    LogDebug("Executing PlaySoundCommand(\"%s\")", command.c_str());
    return PlaySoundFromFile(command) ? "OK" : "Error playing sound";
  }

  const std::string PlaySoundCommand::GetHelp() const
  {
    return 
      "Play sound\n"
      "Parameter: <name of sound>\n"
      "Available sounds\n"
      "\ttbd\n"
      "\ttbd\n"
      "\ttbd\n"
      ;
  }
}
