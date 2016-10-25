#include "PlaySoundCommand.h"
#include "logger.h"
#include "SoundPlayer.h"
#include <string>
#include <sstream>
#include <filesystem>
namespace fs = std::experimental::filesystem;

namespace robo
{
  static bool ends_with(const std::string& value, const std::string& ending)
  {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
  }

  const std::string PlaySoundCommand::operator()(const std::string& command)
  {
    LogDebug("Executing PlaySoundCommand(\"%s\")", command.c_str());
    return PlaySoundFromFile(command) ? "OK" : "Error playing sound";
  }

  const std::string PlaySoundCommand::GetHelp() const
  {
    std::stringstream ss;
    ss << "Plays sounds" << std::endl;
    ss << "Available sounds: " << std::endl;

    for (auto& dirEntry : fs::directory_iterator("Sounds"))
    {
      auto& filename = dirEntry.path().filename().string();
      if (ends_with(filename, ".wav"))
      {
        ss << "\t" << filename.substr(0, filename.size() - 4) << std::endl;
      }
    }

    return ss.str();
  }
}
