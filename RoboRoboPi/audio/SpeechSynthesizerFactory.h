#ifndef SPEECH_SYNTHESIZER_FACTORY_H
#define SPEECH_SYNTHESIZER_FACTORY_H
#include <memory>

namespace robo
{
  class ISpeechSynthesizer;
  class ISoundPlayer;

  class SpeechSynthesizerFactory
  {
  public:
    static ISpeechSynthesizer* Create(ISoundPlayer& soundPlayer);
    static std::unique_ptr<ISpeechSynthesizer> CreateUniquePointer(ISoundPlayer& soundPlayer);
  };
}

#endif /* SPEECH_SYNTHESIZER_FACTORY_H */