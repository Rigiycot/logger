#pragma once

#include "logger/modules/config.hpp"
#include <logger/types.hpp>

#include <vector>

namespace lg
{
  class Console
  {
    public:
      void process();

      void activate();
      void stop();

      Console(const Config& config);

    private:
      friend class Logger;

      Config config;

      bool isActive = false;

      std::vector<LogRecord> buffer;
  };
}
