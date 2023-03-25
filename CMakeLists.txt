# CMake Dora shared library
cmake_minimum_required(VERSION 3.7...3.25)
project(DoraLibrary LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11) # need c++ 11 features
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
add_library(dora SHARED) # output libdora.so/libdora.dylib
target_include_directories(dora PRIVATE ${PROJECT_SOURCE_DIR})
include_directories(dora PRIVATE include)
add_subdirectory(src)