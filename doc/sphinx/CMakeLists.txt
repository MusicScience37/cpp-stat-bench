if(DEFINED ENV{PLANTUML_JAR_PATH})
    set(DEFAULT_PLANTUML_JAR_PATH $ENV{PLANTUML_JAR_PATH})
else()
    set(DEFAULT_PLANTUML_JAR_PATH "")
endif()
set(PLANTUML_JAR_PATH
    "${DEFAULT_PLANTUML_JAR_PATH}"
    CACHE FILEPATH "path of plantuml.jar")

set(STAT_BENCH_SPHINX_OPTIONS
    -D "plantuml=java -jar ${PLANTUML_JAR_PATH}" -D
    "release=${PROJECT_VERSION}" -D
    breathe_projects.stat_bench="${STAT_BENCH_XML_ROOT}")

configure_file(
    ${STAT_BENCH_SOURCE_DIR}/schemas/data_file_schema_v1.json
    ${STAT_BENCH_HTML_ROOT}/schemas/data_file_schema_v1.json COPYONLY)
configure_file(
    ${STAT_BENCH_SOURCE_DIR}/schemas/data_file_schema_v2.json
    ${STAT_BENCH_HTML_ROOT}/schemas/data_file_schema_v2.json COPYONLY)
configure_file(
    ${STAT_BENCH_SOURCE_DIR}/schemas/data_file_schema_v3.json
    ${STAT_BENCH_HTML_ROOT}/schemas/data_file_schema_v3.json COPYONLY)

add_custom_target(
    stat_bench_doc_sphinx_html ALL
    COMMAND
        ${POETRY_EXECUTABLE} run sphinx-build -b html -W
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${STAT_BENCH_HTML_ROOT}
        ${STAT_BENCH_SPHINX_OPTIONS} -q
    COMMENT "Generate Sphinx HTML API documentation for ${FULL_PROJECT_NAME}"
    WORKING_DIRECTORY ${STAT_BENCH_SOURCE_DIR})

add_dependencies(stat_bench_doc stat_bench_doc_sphinx_html)
add_dependencies(stat_bench_doc_sphinx_html stat_bench_doc_doxygen)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start_auto_build.sh.in
               ${CMAKE_CURRENT_BINARY_DIR}/start_auto_build.sh)
