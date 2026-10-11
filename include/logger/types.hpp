#pragma once

#include <chrono>
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
    std::chrono::time_point<std::chrono::system_clock> time;
    std::string message;
  };
}
