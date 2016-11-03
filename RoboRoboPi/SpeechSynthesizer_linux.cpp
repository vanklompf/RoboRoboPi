#include "SpeechSynthesizer.h"
#include <espeak/speak_lib.h>
#include "logger.h"

namespace robo
{
  static int SynthCallback(short *wav, int numsamples, espeak_EVENT *events)
  {
    LogDebug("SynthCallback\n");
    return 0;
  }

  void SpeechSynthesizer::Init()
  {
    if (espeak_Initialize(AUDIO_OUTPUT_SYNCH_PLAYBACK, 0, NULL, espeakINITIALIZE_PHONEME_EVENTS) < 0)
    {
      LogDebug("Could not initialize espeak\n");
    }

    espeak_SetSynthCallback(SynthCallback);
    LogDebug("SpeechSynthesizer Initialized.");
  }

  bool SpeechSynthesizer::Say(std::string phrase)
  {
    auto speakErr = espeak_Synth(phrase.c_str(), phrase.length(), 0, (espeak_POSITION_TYPE)0, 0, espeakCHARS_AUTO, NULL, NULL);
    if (speakErr != EE_OK)
    {
      LogDebug("Error on synth creation: %s\n", speakErr);
      return false;
    }
    return true;
  }
}