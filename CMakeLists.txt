cmake_minimum_required(VERSION 3.12)

if(DEFINED PROJECT_NAME)
    set(STAT_BENCH_SUBPROJECT ON)
else()
    set(STAT_BENCH_SUBPROJECT OFF)
endif()

project(
    stat_bench
    VERSION 0.0.0
    DESCRIPTION "Benchmark library with statistics for C++."
    LANGUAGES CXX)
set(FULL_PROJECT_NAME "cpp-stat-bench")
message(STATUS "${FULL_PROJECT_NAME} version ${PROJECT_VERSION}")
message(STATUS "build type: ${CMAKE_BUILD_TYPE}")

set(BUILDNAME
    "${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}-${CMAKE_BUILD_TYPE}"
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CTestCustom.cmake
               ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
include(CTest)

option(BUILD_SHARED_LIBS "Build shared library" ON)

option(STAT_BENCH_BUILD_DOC "build documentation of ${FULL_PROJECT_NAME}" OFF)
option(STAT_BENCH_TESTING "enable tests of ${FULL_PROJECT_NAME}" OFF)
option(STAT_BENCH_BUILD_EXAMPLES "build examples of ${FULL_PROJECT_NAME}" OFF)

set(CMAKE_CXX_STANDARD
    14
    CACHE STRING "C++ standard")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# find packages installed with Conan
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
find_package(fmt REQUIRED)
find_package(lyra REQUIRED)
find_package(nlohmann_json REQUIRED)
if(STAT_BENCH_TESTING)
    find_package(Catch2 REQUIRED)
    find_package(trompeloeil REQUIRED)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(CppWarningFlags)
include(ConfigureClangTidy)
include(pipenv)

set(STAT_BENCH_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

if(STAT_BENCH_BUILD_DOC)
    add_subdirectory(doc)
endif()

if(STAT_BENCH_TESTING)
    add_subdirectory(tests)
endif()

if(STAT_BENCH_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
