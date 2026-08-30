#pragma once

#include <string>

namespace lg
{
  enum class LogLevel
  {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    CRASH
  };
  
  struct LogRecord
  {
    LogLevel level;
    std::string message;
  };
}
