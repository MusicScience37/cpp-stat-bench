cmake_minimum_required(VERSION 3.12)

project(
    stat_bench_test
    VERSION 0.8.0
    LANGUAGES CXX)
message(STATUS "stat_bench_test version ${PROJECT_VERSION}")
message(STATUS "build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD
    14
    CACHE STRING "C++ standard")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# for find_package
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(cpp_stat_bench REQUIRED)

enable_testing()
add_executable(example example.cpp)
target_link_libraries(example cpp_stat_bench::stat_bench)
add_test(
    NAME example
    COMMAND example
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
