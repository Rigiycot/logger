#pragma once

#include "logger/modules/config.hpp"
#include <logger/types.hpp>

#include <filesystem>
#include <vector>

namespace lg
{
  class FileWriter
  {
    public:
      void process();

      void activate();
      void stop();

      void setDirectory(const std::filesystem::path& path);
      std::filesystem::path getDirectory() const;

      FileWriter(const Config& config);

    private:
      friend class Logger;

      const Config& config;

      bool isActive = false;
      
      std::vector<LogRecord> buffer;
      std::filesystem::path pathToLogsDir = config.logs_dir;
  };
}
