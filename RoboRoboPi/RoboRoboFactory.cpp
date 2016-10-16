#include "RoboRoboFactory.h"
#include "RoboRobo.h"
#include "servo.h"
#include "ServoCommand.h"
#include "HelpCommand.h"
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
    auto robo = new RoboRobo(std::move(servo), std::move(client));

    messageHandler->RegisterCommand('s', std::move(std::make_unique<ServoCommand>(*servo)));
    messageHandler->RegisterCommand('h', std::move(std::make_unique<HelpCommand>()));

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