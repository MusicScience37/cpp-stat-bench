include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_executable(stat_bench_test_units ${SOURCE_FILES})
target_add_catch2(stat_bench_test_units)

add_executable(stat_bench_test_units_unity EXCLUDE_FROM_ALL unity_source.cpp)
target_link_libraries(stat_bench_test_units_unity PRIVATE Catch2::Catch2WithMain
                                                          stat_bench)
target_check_clang_tidy(stat_bench_test_units_unity)
