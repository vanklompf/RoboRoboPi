#ifndef PLAY_SOUND_COMMAND_H
#define PLAY_SOUND_COMMAND_H

#include "commands/ICommand.h"
#include <string>

namespace robo
{
  class ISoundPlayer;

  class PlaySoundCommand final : public ICommand
  {
  public:
    PlaySoundCommand(const ISoundPlayer& soundPlayer);
    const std::string operator()(const std::string& command);
    const std::string GetHelp() const;

  private:
    const ISoundPlayer& m_soundPlayer;
  };
}

#endif /* PLAY_SOUND_COMMAND_H */