cmake_minimum_required(VERSION 4.0)

project(Logger)

add_library(
  Logger
  src/config.cpp
  src/filewriter.cpp
  src/logger.cpp
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
