add_executable(stat_bench_test_integ_groups_and_cases groups_and_cases.cpp)
target_link_libraries(stat_bench_test_integ_groups_and_cases PRIVATE stat_bench)

add_test(
    NAME stat_bench_test_integ
    COMMAND
        ${POETRY_EXECUTABLE} run pytest
        "--junit-xml=${CMAKE_BINARY_DIR}/junit/stat_bench_test_integ.xml"
        --build ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${STAT_BENCH_SOURCE_DIR})
