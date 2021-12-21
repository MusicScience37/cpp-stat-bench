option(STAT_BENCH_WRITE_JUNIT
       "write JUnit XML files in tests of ${FULL_PROJECT_NAME}" OFF)
if(STAT_BENCH_WRITE_JUNIT)
    set(STAT_BENCH_JUNIT_DIR
        "${CMAKE_BINARY_DIR}/junit"
        CACHE PATH "directory to which JUnit XML files are outputed" FORCE)
    file(MAKE_DIRECTORY ${STAT_BENCH_JUNIT_DIR})
endif()

set(STAT_BENCH_TEMP_TEST_DIR
    "${CMAKE_BINARY_DIR}/temp_test"
    CACHE PATH "directory used in test" FORCE)
file(MAKE_DIRECTORY ${STAT_BENCH_TEMP_TEST_DIR})

macro(target_add_catch2 TARGET)
    target_link_libraries(${TARGET} PRIVATE Catch2::Catch2WithMain
                                            trompeloeil::trompeloeil stat_bench)

    if(STAT_BENCH_WRITE_JUNIT)
        set(CATCH2_REPORT_OPTIONS -r junit -o
                                  ${STAT_BENCH_JUNIT_DIR}/${TARGET}.xml)
    else()
        set(CATCH2_REPORT_OPTIONS -r console)
    endif()

    add_test(
        NAME ${TARGET}
        COMMAND ${TARGET} ${CATCH2_REPORT_OPTIONS}
        WORKING_DIRECTORY ${STAT_BENCH_TEMP_TEST_DIR})
endmacro()

add_subdirectory(units)
add_subdirectory(integ)

option(STAT_BENCH_ENABLE_BENCH "enable benchmarks of ${FULL_PROJECT_NAME}" OFF)
if(STAT_BENCH_ENABLE_BENCH)
    # add_subdirectory(bench)
endif()
