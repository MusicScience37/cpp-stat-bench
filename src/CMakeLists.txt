include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(stat_bench STATIC ${SOURCE_FILES})
target_include_directories(stat_bench PUBLIC ${STAT_BENCH_SOURCE_DIR}/include)
set_target_properties(stat_bench PROPERTIES VERSION ${PROJECT_VERSION})
