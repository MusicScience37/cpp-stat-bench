find_package(Doxygen REQUIRED dot)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
               ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

file(MAKE_DIRECTORY ${STAT_BENCH_HTML_ROOT}/api)
file(MAKE_DIRECTORY ${STAT_BENCH_XML_ROOT})

add_custom_target(
    stat_bench_doc_doxygen ALL
    COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    COMMENT
        "Generate Doxygen HTML / XML API documentation for ${FULL_PROJECT_NAME}"
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${STAT_BENCH_SOURCE_DIR})

add_dependencies(stat_bench_doc stat_bench_doc_doxygen)
