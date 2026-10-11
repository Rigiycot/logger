#include "logger/modules/config.hpp"
#include <logger/modules/console.hpp>

#include <logger/types.hpp>

#include <iostream>
#include <string>

namespace
{
  std::string color(lg::LogLevel level)
  {
    switch (level)
    {
      case lg::LogLevel::DEBUG:
        return "\033[38;5;17m";
      case lg::LogLevel::INFO:
        return "\033[38;5;255m";
      case lg::LogLevel::WARN:
        return "\033[38;5;220m";
      case lg::LogLevel::ERROR:
        return "\033[38;5;196m";
      case lg::LogLevel::CRASH:
        return "\033[38;5;165m";
      default:
        return {};
    }
  }

  std::string levelToName(const lg::Config& config, lg::LogLevel level)
  {
    switch (level)
    {
      case lg::LogLevel::DEBUG:
        return config.debug;
      case lg::LogLevel::INFO:
        return config.info;
      case lg::LogLevel::WARN:
        return config.warn;
      case lg::LogLevel::ERROR:
        return config.error;
      case lg::LogLevel::CRASH:
        return config.crash;
      default:
        return {};
    }
  }

  std::string formatTime(std::chrono::system_clock::time_point tp, const char* fmt)
  {
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    std::tm time_local = *std::localtime(&time);

    std::stringstream ss;

    ss << std::put_time(&time_local, fmt);
    return ss.str();
  }
}

lg::Console::Console(const lg::Config& config)
  : config(config)
{}

void lg::Console::process()
{
  for (const LogRecord& rec : this->buffer)
  {
    if (config.console_show_time && config.console_colorize)
      std::cerr << color(rec.level)
                << "[" << ::formatTime(rec.time, "%H:%M:%S") << "]"
                << config.left
                << ::levelToName(this->config, rec.level)
                << config.right
                << " " 
                << rec.message
                << "\033[0m\n";

    else if (config.console_show_time)
      std::cerr << "[" << ::formatTime(rec.time, "%H:%M:%S") << "]"
                << config.left
                << ::levelToName(this->config, rec.level)
                << config.right
                << " " 
                << rec.message
                << "\n";

    else if (config.console_colorize)
      std::cerr << color(rec.level)
                << config.left
                << ::levelToName(this->config, rec.level)
                << config.right
                << " " 
                << rec.message
                << "\033[0m\n";

    else
      std::cerr << config.left
                << ::levelToName(this->config, rec.level)
                << config.right
                << " " 
                << rec.message
                << "\n";
  }

  this->buffer.clear();
}

void lg::Console::activate()
{
  this->isActive = true;
}

void lg::Console::stop()
{
  this->isActive = false;
}
