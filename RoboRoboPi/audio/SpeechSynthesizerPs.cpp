#include "audio/SpeechSynthesizerPs.h"
#include <io.h>
#include <string>

namespace robo
{
  bool SpeechSynthesizerPs::Say(std::string phrase)
  {
    std::string script = "powershell -executionPolicy bypass -file audio/speak.ps1 \"" + phrase + "\"";
    return system(script.c_str()) >= 0;
  }
}