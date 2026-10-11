#pragma once

#include <logger/types.hpp>

#include <filesystem>
#include <set>
#include <string>

namespace lg
{
  class Logger;

  struct Config
  {
    std::string debug = "DEBUG";
    std::string info  = "INFO";
    std::string warn  = "WARN";
    std::string error = "ERROR";
    std::string crash = "CRASH";

    std::set<LogLevel> filter_console;
    std::set<LogLevel> filter_filer;

    std::string left = "[";
    std::string right = "]";

    bool console_show_time = false;
    bool console_colorize = true;

    bool filer_show_time = true;

    std::filesystem::path logs_dir = "logs";

    void getFromPath(const std::filesystem::path& path); // must be .conf file, but not role
  };
}
