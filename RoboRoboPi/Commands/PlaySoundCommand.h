#ifndef PLAY_SOUND_COMMAND_H
#define PLAY_SOUND_COMMAND_H

#include "ICommand.h"
#include <string>

namespace robo
{
  class PlaySoundCommand final : public ICommand
  {
  public:
    const std::string operator()(const std::string& command);
    const std::string PlaySoundCommand::GetHelp() const;
  };
}

#endif /* PLAY_SOUND_COMMAND_H */