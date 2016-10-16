#ifndef ROBO_ROBO_FACTORY_H
#define ROBO_ROBO_FACTORY_H

namespace gloox
{
  class Client;
}

namespace robo
{
  class RoboRobo;

  class RoboRoboFactory final
  {
  public:
    static RoboRobo* Create();

  private:
    static gloox::Client* CreateClient();
  };
}
#endif /* ROBO_ROBO_FACTORY_H */
