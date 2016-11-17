#include "SpeechSynthesizerFactory.h"
#include "ISpeechSynthesizer.h"
#ifdef __linux__ 
#include "SpeechSynthesizerTts.h"
#elif _WIN32
#include "SpeechSynthesizerPs.h"
#endif

namespace robo
{
  ISpeechSynthesizer * SpeechSynthesizerFactory::Create(ISoundPlayer& soundPlayer)
  {
#ifdef __linux__ 
    return new SpeechSynthesizerTts(soundPlayer);
#elif _WIN32
    return new SpeechSynthesizerPs();
#endif
  }

  std::unique_ptr<ISpeechSynthesizer> SpeechSynthesizerFactory::CreateUniquePointer(ISoundPlayer& soundPlayer)
  {
    return std::unique_ptr<ISpeechSynthesizer>(Create(soundPlayer));
  }
}
