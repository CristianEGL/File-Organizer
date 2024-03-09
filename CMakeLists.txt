cmake_minimum_required(VERSION 3.29)
project(Sorcerers-Stash)

# Assuming that the source files are in a directory named "src" relative to the CMakeLists.txt file
include_directories(include)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(SOURCE_FILES src/sorcerers-stash.c src/list_functions.c src/file_functions.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(stash ${SOURCE_FILES})

# Optionally, specify any additional dependencies or compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")