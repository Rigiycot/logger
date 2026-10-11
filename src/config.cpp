#include "logger/types.hpp"
#include <cstddef>
#include <logger/modules/config.hpp>

#include <fstream>
#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <string>


namespace
{
  lg::LogLevel toLevel(const std::string& s)
  {
    if (s == "DEBUG")
      return lg::LogLevel::DEBUG;
    else if (s == "INFO")
      return lg::LogLevel::INFO;
    else if (s == "WARN")
      return lg::LogLevel::WARN;
    else if (s == "ERROR")
      return lg::LogLevel::ERROR;
    else if (s == "CRASH")
      return lg::LogLevel::CRASH;
    else
      throw std::runtime_error("Unknown name " + s);
  }
}


void lg::Config::getFromPath(const std::filesystem::path& path)
{
  std::ifstream file(path);

  if (!file.is_open())
    return;

  std::string sector;
  std::string line;

  std::size_t lineNum = 0;

  while (std::getline(file, line))
  {
    ++lineNum;

    if (line.empty())
      continue;

    std::erase_if(line, [](unsigned char c) { return std::isspace(c) != 0; });


    // conditions
    if (std::size_t pos = line.find("//"); pos != std::string::npos)
      line.erase(pos);

    std::replace(line.begin(), line.end(), '-', ' ');

    if (line.size() >= 2 && line.front() == '[' && line.back() == ']')
    {
      sector = line;
      continue;
    }
    
    if (std::size_t eq = line.find('='); eq != std::string::npos)
    {
      std::string key = line.substr(0, eq);
      std::string value = line.substr(eq + 1);

      if (sector == "[Logger]")
      {
        if (std::count(line.begin(), line.end(), '=') != 1)
          throw std::runtime_error("Waited 1 '=', but get more");

        if (key.empty() || value.empty())
          throw std::runtime_error("Unexpected empty field at " + std::to_string(lineNum));

        if (key == "debug")
          this->debug = value;

        else if (key == "info")
          this->info = value;

        else if (key == "warn")
          this->warn = value;

        else if (key == "error")
          this->error = value;

        else if (key == "crash")
          this->crash = value;


        else if (key == "left")
          this->left = value;

        else if (key == "right")
          this->right = value;


        else
          throw std::runtime_error("Unknown name: " + key + " in [Logger]");
      }
      else if (sector == "[Console]")
      {
        if (key == "show_time")
          if (value == "true")
            this->console_show_time = true;
          else if (value == "false")
            this->console_show_time = false;
          else
            throw std::runtime_error("Bad value: " + std::to_string(lineNum));

        else if (key == "colorize")
        {
          if (value == "true")
            this->console_colorize = true;
          else if (value == "false")
            this->console_colorize = false;
          else
            throw std::runtime_error("Bad value: " + std::to_string(lineNum));
        }
      }

      if (key == "filter")
      {
        if (value.size() < 2 || value.front() != '{' || value.back() != '}')
          throw std::runtime_error("Filter must be {DEBUG/INFO/WARN/ERROR/CRASH}, got " + value);
        
        std::string inner = value.substr(1, value.size() - 2);

        std::set<lg::LogLevel> result;

        while (!inner.empty())
        {
          std::size_t comma = inner.find(',');
          std::string token = inner.substr(0, comma);

          result.insert(::toLevel(token));

          if (comma == std::string::npos)
            inner.clear();
          else
            inner = inner.substr(comma + 1);
        }

        if (sector == "[Console]")
          this->filter_console = std::move(result);
        else if (sector == "[FileWriter]")
          this->filter_filer = std::move(result);
      }
      continue;
    }

    std::string error_string = std::to_string(lineNum) + ": " + line + "";
    throw std::runtime_error(error_string);
  }
}
