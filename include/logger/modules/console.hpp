#pragma once

#include <vector>

namespace lg
{
  struct LogRecord;

  class Console
  {
    public:
      void process();

      void activate();
      void stop();

    private:
      friend class Logger;

      bool isActive = false;

      std::vector<LogRecord> buffer;
  };
}
