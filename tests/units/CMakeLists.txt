include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_executable(stat_bench_test_units ${SOURCE_FILES} test_main.cpp)
target_add_catch2(stat_bench_test_units)
if(STAT_BENCH_ENABLE_PRECOMPILED_HEADERS)
    target_precompile_headers(stat_bench_test_units PRIVATE <fmt/format.h>
                              <catch2/catch_test_macros.hpp>)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(
            stat_bench_test_units
            PRIVATE
                "$<$<COMPILE_LANGUAGE:CXX>:SHELL:-Xclang -fno-pch-timestamp>")
    endif()
endif()

file(MAKE_DIRECTORY ${STAT_BENCH_TEMP_TEST_DIR}/plots)

add_executable(stat_bench_test_units_unity EXCLUDE_FROM_ALL unity_source.cpp)
target_link_libraries(stat_bench_test_units_unity PRIVATE Catch2::Catch2WithMain
                                                          stat_bench)
