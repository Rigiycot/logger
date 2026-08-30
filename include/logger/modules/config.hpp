#pragma once

#include <filesystem>
#include <set>
#include <string>

namespace lg
{
  class Logger;
  enum class LogLevel;

  class Config
  {
    public:
      bool immediate = false;

      std::string debug = "DEBUG";
      std::string info  = "INFO";
      std::string warn  = "WARN";
      std::string error = "ERROR";
      std::string crash = "CRASH";

      std::set<LogLevel> filter_filer;
      std::set<LogLevel> filter_console;

      std::string left = "[";
      std::string right = "]";

      std::filesystem::path logs_dir = "logs";

      void getFromPath(const std::filesystem::path& path); // must be .conf file, but not role
  
      void activate();
      void stop();

      Config(Logger& logger);

    private:
      bool isActive = false;
  };
}
