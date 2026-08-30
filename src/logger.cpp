#include <logger/logger.hpp>

#include <logger/types.hpp>

#include <string>

void lg::Logger::log(lg::LogLevel level, const std::string message)
{
  this->buffer.push_back({level, message});
}

void lg::Logger::debug(const std::string& message)
{
  this->log(lg::LogLevel::DEBUG, message);
}

void lg::Logger::info(const std::string& message)
{
  this->log(lg::LogLevel::INFO, message);
}

void lg::Logger::warn(const std::string& message)
{
  this->log(lg::LogLevel::WARN, message);
}

void lg::Logger::error(const std::string& message)
{
  this->log(lg::LogLevel::ERROR, message);
}

void lg::Logger::crash(const std::string& message)
{
  this->log(lg::LogLevel::CRASH, message);
}

void lg::Logger::process()
{
  for (lg::LogRecord& rec : this->buffer)
  {
    if (this->config.filter_filer.contains(rec.level) && this->filer.isActive)
    {
      this->filer.buffer.push_back(rec);
    }

    if (this->config.filter_console.contains(rec.level) && this->console.isActive)
    {
      this->console.buffer.push_back(rec);
    }
  }

  this->buffer.clear();
}

void lg::Logger::exec()
{
  if (this->console.isActive)
    this->console.process();
}
