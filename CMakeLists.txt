cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Logger)

add_library(
  Logger
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
