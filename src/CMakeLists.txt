include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(stat_bench ${SOURCE_FILES})
target_include_directories(stat_bench PUBLIC ${STAT_BENCH_SOURCE_DIR}/include
                                             ${CMAKE_BINARY_DIR}/include)
set_target_properties(
    stat_bench
    PROPERTIES CXX_VISIBILITY_PRESET hidden
               VISIBILITY_INLINES_HIDDEN 1
               POSITION_INDEPENDENT_CODE ON
               VERSION ${PROJECT_VERSION})
include(GenerateExportHeader)
generate_export_header(
    stat_bench
    EXPORT_FILE_NAME
        "${CMAKE_BINARY_DIR}/include/stat_bench/impl/stat_bench_export.h")
