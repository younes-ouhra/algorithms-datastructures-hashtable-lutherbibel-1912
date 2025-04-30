cmake_minimum_required(VERSION 3.16)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "generate compile_commands.json")

# Verbose build output
# set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "enable verbose build")

project(hashtable CXX C)

# Define sources and executable
add_executable(${PROJECT_NAME} main.cpp WordHash.cpp WordHashItem.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -g -Wall -Wextra)

