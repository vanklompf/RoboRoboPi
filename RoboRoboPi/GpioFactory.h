#ifndef GPIO_FACTORY_H
#define GPIO_FACTORY_H
#include <memory>

namespace robo
{
  class IGpio;

  class GpioFactory
  {
  public:
    static IGpio* Create();
    static std::unique_ptr<IGpio> CreateUniquePointer();
  };
}

#endif /* GPIO_FACTORY_H */