cmake_minimum_required(VERSION 3.0.0)
project(HashTable
 VERSION 0.1.0
 LANGUAGES CXX)


add_subdirectory(HashLib)
include_directories(HashLib) # make header files available in cpp files for easy include #include "lib.h" not #include "path/to/lib.h"

add_executable(${PROJECT_NAME}
 hashing.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE HashLib)


# Todo
# - way to debug: debug symbols
# - hacky build: with some options enabled, plus debug symbols