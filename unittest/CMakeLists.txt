# Dora library unittest
cmake_minimum_required(VERSION 3.7...3.25)
project(DoraLibTest LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# Location of Dora shared library and Dora headers
# Note in mac use "libdora.dylib"
set(dora_shared_lib ${PROJECT_SOURCE_DIR}/../build/lib/libdora.so)
set(dora_header_path ${PROJECT_SOURCE_DIR}/../include/)

# Import Dora shared library
add_library(doralib SHARED IMPORTED)
set_target_properties(doralib PROPERTIES IMPORTED_LOCATION ${dora_shared_lib})

# Put executable in bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
add_executable(unit_test_assert)
target_include_directories(unit_test_assert PUBLIC ${dora_header_path})
target_link_libraries(unit_test_assert doralib)
target_sources(unit_test_assert PRIVATE test_assert.cpp)