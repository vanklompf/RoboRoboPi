#include "RoboRoboFactory.h"
#include "RoboRobo.h"
#include "IGpio.h"
#include "GpioFactory.h"
#include "audio/ISpeechSynthesizer.h"
#include "audio/ISoundPlayer.h"
#include "audio/SpeechSynthesizerFactory.h"
#include "audio/SoundPlayerFactory.h"
#include "commands/ServoCommand.h"
#include "commands/LedCommand.h"
#include "commands/TellCommand.h"
#include "commands/PlaySoundCommand.h"
#include "commands/HelpCommand.h"
#include "commands/UnknownCommand.h"
#include "MessageHandler.h"
#include "ConnectionListener.h"

#include "gloox/src/client.h"
#include <memory>

namespace robo
{
  RoboRobo* RoboRoboFactory::Create()
  {
    auto client = std::unique_ptr<gloox::Client>(CreateClient());
    auto commandsMap = std::make_unique<CommandsMap>();
    const CommandsMap& commandsMapRef = *commandsMap;
    auto messageHandler = new MessageHandler(*client, std::move(commandsMap));
    auto connectionListener = new ConnectionListener(*client);

    client->registerMessageHandler(messageHandler);
    client->registerConnectionListener(connectionListener);

    auto soundPlayer = SoundPlayerFactory::CreateUniquePointer();
    auto synthesizer = SpeechSynthesizerFactory::CreateUniquePointer(*soundPlayer);
    auto gpio = GpioFactory::CreateUniquePointer();


    messageHandler->RegisterDefaultCommand(std::move(std::make_unique<UnknownCommand>()));
    messageHandler->RegisterCommand('s', std::move(std::make_unique<ServoCommand>(*gpio)));
    messageHandler->RegisterCommand('l', std::move(std::make_unique<LedCommand>(*gpio)));
    messageHandler->RegisterCommand('t', std::move(std::make_unique<TellCommand>(*synthesizer)));
    messageHandler->RegisterCommand('p', std::move(std::make_unique<PlaySoundCommand>(*soundPlayer)));
    messageHandler->RegisterCommand('h', std::move(std::make_unique<HelpCommand>(commandsMapRef)));

    auto robo = new RoboRobo(std::move(gpio), std::move(soundPlayer), std::move(synthesizer), std::move(client));
    return robo;
  }

  gloox::Client* RoboRoboFactory::CreateClient()
  {
    auto client = new gloox::Client("city.gov");
    client->setUsername("robo");
    client->setPassword("abcd");
    client->setServer("centosxmpp.westeurope.cloudapp.azure.com");
    client->disableRoster();

    return client;
  }
}