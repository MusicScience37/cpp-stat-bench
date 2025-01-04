option(STAT_BENCH_TEST_EXAMPLES "Test execution of examples" OFF)

function(add_example TARGET)
    add_executable(${TARGET} ${ARGN})
    target_link_libraries(${TARGET} PRIVATE stat_bench)
    if(STAT_BENCH_TESTING AND STAT_BENCH_TEST_EXAMPLES)
        add_test(
            NAME ${TARGET}
            COMMAND $<TARGET_FILE:${TARGET}> --plot
                    "${STAT_BENCH_TEMP_TEST_DIR}/${TARGET}"
            WORKING_DIRECTORY ${STAT_BENCH_TEMP_TEST_DIR})
    endif()
endfunction()

add_example(stat_bench_ex_bench_for bench_for.cpp)

add_example(stat_bench_ex_bench_fibonacci bench_fibonacci.cpp)

add_example(stat_bench_ex_bench_push_back bench_push_back.cpp)

add_example(stat_bench_ex_bench_containers bench_containers.cpp)
