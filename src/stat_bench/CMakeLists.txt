include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(stat_bench STATIC ${SOURCE_FILES})
target_include_directories(
    stat_bench PUBLIC $<BUILD_INTERFACE:${STAT_BENCH_SOURCE_DIR}/include>
                      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(
    stat_bench
    PUBLIC fmt::fmt
           bfg::lyra
           nlohmann_json::nlohmann_json
           cpp_msgpack_light::msgpack_light
           ZLIB::ZLIB
           Eigen3::Eigen
           $<BUILD_INTERFACE:stat_bench_cpp_warnings>)
target_link_libraries(stat_bench PRIVATE pantor::inja)
set_target_properties(stat_bench PROPERTIES VERSION ${PROJECT_VERSION})
target_compile_features(stat_bench PUBLIC cxx_std_14)
target_compile_features(stat_bench PRIVATE cxx_std_17)
if(MSVC)
    target_compile_definitions(stat_bench PUBLIC _CRT_SECURE_NO_WARNINGS=1)
endif()
target_add_ausan(stat_bench)

target_link_libraries(stat_bench PUBLIC Threads::Threads)

if(MSVC)
    target_compile_options(stat_bench PUBLIC /EHsc /utf-8)
endif()

add_library(stat_bench_unity EXCLUDE_FROM_ALL unity_source.cpp)
target_include_directories(
    stat_bench_unity PUBLIC $<BUILD_INTERFACE:${STAT_BENCH_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(
    stat_bench_unity
    PUBLIC fmt::fmt
           bfg::lyra
           nlohmann_json::nlohmann_json
           cpp_msgpack_light::msgpack_light
           ZLIB::ZLIB
           Eigen3::Eigen
           Threads::Threads
           $<BUILD_INTERFACE:stat_bench_cpp_warnings>)
target_link_libraries(stat_bench_unity PRIVATE pantor::inja)
set_target_properties(stat_bench_unity PROPERTIES VERSION ${PROJECT_VERSION})
target_compile_features(stat_bench_unity PUBLIC cxx_std_14)
target_compile_features(stat_bench_unity PRIVATE cxx_std_17)
