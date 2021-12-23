message("Configure documentation of ${FULL_PROJECT_NAME}")

add_custom_target(stat_bench_doc)

set(STAT_BENCH_HTML_ROOT ${CMAKE_CURRENT_BINARY_DIR}/html)

add_subdirectory(doxygen)

option(STAT_BENCH_BUILD_DOC_SPHINX
       "build documentation of ${FULL_PROJECT_NAME} with Sphinx" ON)
if(STAT_BENCH_BUILD_DOC_SPHINX)
    add_subdirectory(sphinx)
endif()
