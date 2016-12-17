#include "GpioFactory.h"
#ifdef __linux__ 
#include "GpioPi.h"
#elif _WIN32
#include "GpioWin.h"
#endif

namespace robo
{
  IGpio* GpioFactory::Create()
  {
#ifdef __linux__ 
    return new GpioPi();
#elif _WIN32
    return new GpioWin();
#endif
  }
  
  std::unique_ptr<IGpio> GpioFactory::CreateUniquePointer()
  {
    return std::unique_ptr<IGpio>(Create());
  }
}