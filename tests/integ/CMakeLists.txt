function(stat_bench_test_integ_add_bench BENCH_NAME)
    add_executable(stat_bench_test_integ_${BENCH_NAME} ${BENCH_NAME}.cpp)
    target_link_libraries(stat_bench_test_integ_${BENCH_NAME}
                          PRIVATE stat_bench)
endfunction()

stat_bench_test_integ_add_bench(simple_benchmark)
stat_bench_test_integ_add_bench(groups_and_cases)
stat_bench_test_integ_add_bench(error_in_benchmark)
stat_bench_test_integ_add_bench(parametrized_benchmark)
stat_bench_test_integ_add_bench(duplicate_cases)
stat_bench_test_integ_add_bench(escaped_names)
stat_bench_test_integ_add_bench(subplots)
stat_bench_test_integ_add_bench(custom_measurement)

add_test(
    NAME stat_bench_test_integ
    COMMAND
        ${POETRY_EXECUTABLE} run pytest
        "--junit-xml=${CMAKE_BINARY_DIR}/junit/stat_bench_test_integ.xml"
        --build ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${STAT_BENCH_SOURCE_DIR})
