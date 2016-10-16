#ifndef LOGGER_H
#define LOGGER_H

namespace robo
{
  void InitLogger(const char* filePeth);
  void CloseLogger();
  void LogDebug(const char * format, ...);
}

#endif /* LOGGER_H */