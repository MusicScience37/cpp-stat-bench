add_executable(stat_bench_test_integ_define_and_register_case
               define_and_register_case.cpp)
target_add_catch2(stat_bench_test_integ_define_and_register_case)

add_executable(stat_bench_test_integ_use_fixture use_fixture.cpp)
target_add_catch2(stat_bench_test_integ_use_fixture)

add_executable(stat_bench_test_integ_example_benchmark example_benchmark.cpp)
target_link_libraries(stat_bench_test_integ_example_benchmark
                      PRIVATE stat_bench)
add_test(
    NAME stat_bench_test_integ_example_benchmark
    COMMAND stat_bench_test_integ_example_benchmark --plot ./ --samples 5
            --mean_samples 5
    WORKING_DIRECTORY ${STAT_BENCH_TEMP_TEST_DIR})

add_executable(stat_bench_test_integ_error_in_benchmark error_in_benchmark.cpp)
target_link_libraries(stat_bench_test_integ_error_in_benchmark
                      PRIVATE stat_bench)
add_test(
    NAME stat_bench_test_integ_error_in_benchmark
    COMMAND stat_bench_test_integ_error_in_benchmark --plot ./ --samples 5
            --mean_samples 5
    WORKING_DIRECTORY ${STAT_BENCH_TEMP_TEST_DIR})
