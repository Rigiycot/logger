cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Logger)


if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(
  Logger
  SHARED
  src/config.cpp
  src/filewriter.cpp
  src/logger.cpp
  src/console.cpp
)

target_include_directories(
  Logger
  PUBLIC
  include
)

target_compile_features(
  Logger
  PUBLIC
  cxx_std_23
)
