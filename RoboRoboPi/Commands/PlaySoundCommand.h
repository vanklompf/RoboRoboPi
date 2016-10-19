#ifndef PLAY_SOUND_COMMAND_H
#define PLAY_SOUND_COMMAND_H

#include "ICommand.h"
#include <string>

namespace robo
{
  class PlaySoundCommand final : public ICommand
  {
  public:
    std::string operator()(const std::string& command);
  };
}

#endif /* PLAY_SOUND_COMMAND_H */