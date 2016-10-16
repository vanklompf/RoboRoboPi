#include "logger.h"
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <time.h>

using namespace std;

namespace robo
{
  static ofstream logFile;
  static char tmpLogBuffer[1000];

  void InitLogger(const char* filePath)
  {
    logFile.open(filePath, ofstream::out | ofstream::app);
    if (!logFile.is_open())
    {
      printf("Error opening log file: %s", filePath);
    }
  }

  void CloseLogger()
  {
    if (logFile.is_open())
    {
      logFile.close();
    }
  }

  static const char* GetTimestamp(const char* format)
  {
    static char date[25];
    time_t t = time(0);
    struct tm *tm;
    tm = gmtime(&t);
    strftime(date, sizeof(date), format, tm);

    return date;
  }

  static const char* GetFileTimestamp()
  {
    return GetTimestamp("%F %T%t");
  }

  static const char* GetConsoleTimestamp()
  {
    return GetTimestamp("%T%t");
  }


  void LogDebug(const char * format, ...)
  {
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(tmpLogBuffer, 999, format, argptr);
    va_end(argptr);

    logFile << GetFileTimestamp() << tmpLogBuffer << endl;
    cout << GetConsoleTimestamp() << tmpLogBuffer << endl;
  }
}