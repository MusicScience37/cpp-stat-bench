include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(stat_bench STATIC ${SOURCE_FILES})
target_include_directories(
    stat_bench PUBLIC $<BUILD_INTERFACE:${STAT_BENCH_SOURCE_DIR}/include>
                      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(stat_bench PUBLIC fmt::fmt bfg::lyra
                                        nlohmann_json::nlohmann_json)
target_link_libraries(stat_bench PRIVATE pantor::inja)
set_target_properties(stat_bench PROPERTIES VERSION ${PROJECT_VERSION})
target_compile_features(stat_bench PUBLIC cxx_std_14)
target_compile_features(stat_bench PRIVATE cxx_std_17)
target_check_clang_tidy(stat_bench)

target_link_libraries(stat_bench PUBLIC Threads::Threads)

if(MSVC)
    target_compile_options(stat_bench PUBLIC /EHsc /utf-8)
endif()