#pragma once

#include <filesystem>
#include <vector>

namespace lg
{
  struct LogRecord;

  class FileWriter
  {
    public:
      bool isActive = false;

      void process();

      void setDirectory(std::filesystem::path path);
      std::filesystem::path getDirectory() const;

    private:
      friend class Logger;

      std::vector<LogRecord> buffer;
      std::filesystem::path pathToLogsDir;
  };
}
