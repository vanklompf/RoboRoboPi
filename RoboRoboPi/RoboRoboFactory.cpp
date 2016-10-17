#include "RoboRoboFactory.h"
#include "RoboRobo.h"
#include "servo.h"
#include "Gpio.h"
#include "ServoCommand.h"
#include "LedCommand.h"
#include "HelpCommand.h"
#include "UnknownCommand.h"
#include "MessageHandler.h"
#include "ConnectionListener.h"

#include "gloox\src\client.h"
#include <memory>

namespace robo
{
  RoboRobo* RoboRoboFactory::Create()
  {
    auto client = std::unique_ptr<gloox::Client>(CreateClient());
    auto messageHandler = new MessageHandler(*client);
    auto connectionListener = new ConnectionListener(*client);

    client->registerMessageHandler(messageHandler);
    client->registerConnectionListener(connectionListener);

    auto servo = std::make_unique<Servo>();
    auto gpio = std::make_unique<Gpio>();

    messageHandler->RegisterDefaultCommand(std::move(std::make_unique<UnknownCommand>()));
    messageHandler->RegisterCommand('s', std::move(std::make_unique<ServoCommand>(*servo)));
    messageHandler->RegisterCommand('l', std::move(std::make_unique<LedCommand>(*gpio)));
    messageHandler->RegisterCommand('h', std::move(std::make_unique<HelpCommand>()));

    auto robo = new RoboRobo(std::move(servo), std::move(client));
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