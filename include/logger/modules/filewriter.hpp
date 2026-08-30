#pragma once

#include <logger/types.hpp>

#include <filesystem>
#include <vector>

namespace lg
{
  class FileWriter
  {
    public:
      void process();

      void setDirectory(std::filesystem::path path);
      std::filesystem::path getDirectory() const;

    private:
      friend class Logger;

      bool isActive = false;
      
      std::vector<LogRecord> buffer;
      std::filesystem::path pathToLogsDir;
  };
}
