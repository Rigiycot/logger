#include <iomanip>
#include <logger/modules/config.hpp>
#include <logger/modules/filewriter.hpp>

#include <logger/types.hpp>

#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include <chrono>


namespace
{
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


lg::FileWriter::FileWriter(const Config& config)
  : config(config)
{}

void lg::FileWriter::setDirectory(const std::filesystem::path& path)
{
  this->pathToLogsDir = path;
}

void lg::FileWriter::process()
{
  if (this->buffer.empty())
    return;

  std::filesystem::create_directories(this->pathToLogsDir);

  std::string date = formatTime(std::chrono::system_clock::now(), "%Y-%m-%d");

  std::ofstream file(this->pathToLogsDir / (date + ".log"), std::ios::app);

  if (!file.is_open())
    return;

  for (lg::LogRecord& rec : this->buffer)
  {
    if (config.filer_show_time)
      file << "[" << formatTime(rec.time, "%H:%M:%S") << "]"
          << config.left
          << ::levelToName(this->config, rec.level)
          << config.right
          << " " 
          << rec.message
          << "\n";
    else
      file << config.left
          << ::levelToName(this->config, rec.level)
          << config.right
          << " " 
          << rec.message
          << "\n";
  }

  this->buffer.clear();
}

void lg::FileWriter::activate()
{
  this->isActive = true;
}

void lg::FileWriter::stop()
{
  this->isActive = false;
}
