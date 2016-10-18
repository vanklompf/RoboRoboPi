#include "SpeechSynthesizer.h"

#include <io.h>

namespace robo
{
  int Say(std::string phrase)
  {
    std::string script = "powershell -executionPolicy bypass -file speak.ps1 \"" + phrase + "\"";
    return system(script.c_str());
  }
}