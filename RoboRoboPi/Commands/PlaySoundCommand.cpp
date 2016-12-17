#include "commands/PlaySoundCommand.h"
#include "logger.h"
#include "audio/ISoundPlayer.h"
#include <string>
#include <sstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace robo
{
  static const std::string SOUND_PATH = "sounds";
  
  static bool ends_with(const std::string& value, const std::string& ending)
  {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
  }

  PlaySoundCommand::PlaySoundCommand(const ISoundPlayer& soundPlayer) : m_soundPlayer(soundPlayer)
  {
  }

  const std::string PlaySoundCommand::operator()(const std::string& command)
  {
    std::string filename = SOUND_PATH + "/" + command + ".wav";
    return m_soundPlayer.PlayWav(filename) ? "OK" : "Error playing sound";
  }

  const std::string PlaySoundCommand::GetHelp() const
  {
    std::stringstream ss;
    ss << "Plays sounds" << std::endl;
    ss << "Available sounds: " << std::endl;

    for (auto& dirEntry : fs::directory_iterator(SOUND_PATH))
    {
      const auto& filename = dirEntry.path().filename().string();
      if (ends_with(filename, ".wav"))
      {
        ss << "\t" << filename.substr(0, filename.size() - 4) << std::endl;
      }
    }

    return ss.str();
  }
}
