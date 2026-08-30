#pragma once

#include <logger/modules/config.hpp>
#include <logger/modules/filewriter.hpp>
#include <logger/modules/console.hpp>

#include <string>
#include <vector>

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

  class Logger
  {
    public:
      Config config;
      FileWriter filer;
      Console console;

      void debug(const std::string& message);
      void info (const std::string& message);
      void warn (const std::string& message);
      void error(const std::string& message);
      void crash(const std::string& message);

      void process();

    private:
      std::vector<LogRecord> buffer;

      void log(LogLevel level, const std::string message);
  };
}
