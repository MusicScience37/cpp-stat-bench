cmake_minimum_required(VERSION 3.12)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ParseVersion)
parse_version(${CMAKE_CURRENT_SOURCE_DIR}/include/stat_bench/version.h
              STAT_BENCH)

project(
    stat_bench
    VERSION ${STAT_BENCH_VERSION}
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

# ##############################################################################
# Options.
# ##############################################################################
option(BUILD_SHARED_LIBS "Build shared library" ON)

option(STAT_BENCH_BUILD_DOC "build documentation of ${FULL_PROJECT_NAME}" OFF)
option(STAT_BENCH_TESTING "enable tests of ${FULL_PROJECT_NAME}" OFF)
option(STAT_BENCH_BUILD_EXAMPLES "build examples of ${FULL_PROJECT_NAME}" OFF)
option(STAT_BENCH_ENABLE_INSTALL
       "enable CMake target to install ${FULL_PROJECT_NAME}" ON)
option(STAT_BENCH_ENABLE_PRECOMPILED_HEADERS "enable precompiled headers." OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "export compile commands" FORCE)

# ##############################################################################
# Libraries.
# ##############################################################################
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(lyra REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(inja REQUIRED)
find_package(cpp-msgpack-light REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(simdutf REQUIRED)
find_package(cpp-plotly-plotter REQUIRED)
if(STAT_BENCH_TESTING)
    find_package(Catch2 REQUIRED)
    find_package(trompeloeil REQUIRED)

    # ApprovalTests.
    find_path(APPROVAL_TESTS_CPP_INCLUDE_DIRS "ApprovalTests.hpp")
    add_library(ApprovalTests_ApprovalTests INTERFACE)
    target_include_directories(ApprovalTests_ApprovalTests
                               INTERFACE ${APPROVAL_TESTS_CPP_INCLUDE_DIRS})
    add_library(ApprovalTests::ApprovalTests ALIAS ApprovalTests_ApprovalTests)
endif()

# ##############################################################################
# Configurations.
# ##############################################################################
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)

include(CppWarningFlags)
include(ConfigureSanitizer)
include(poetry)
include(ConfigureCcache)

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

if(STAT_BENCH_ENABLE_INSTALL)
    install(
        TARGETS stat_bench
        EXPORT cpp-stat-bench-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_PREFIX})

    install(
        DIRECTORY ${STAT_BENCH_SOURCE_DIR}/include/stat_bench
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN "*.h*")

    install(
        EXPORT cpp-stat-bench-targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpp-stat-bench
        NAMESPACE cpp_stat_bench::)

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        cmake/cpp-stat-bench-config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/cpp-stat-bench-config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-stat-bench")

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cpp-stat-bench-config.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-stat-bench")
endif()
