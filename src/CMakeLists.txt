include(${CMAKE_CURRENT_SOURCE_DIR}/source_list.cmake)
add_library(stat_bench STATIC ${SOURCE_FILES})
target_include_directories(stat_bench PUBLIC ${STAT_BENCH_SOURCE_DIR}/include
                                             ${CMAKE_BINARY_DIR}/include)
target_link_libraries(stat_bench PUBLIC fmt::fmt bfg::lyra
                                        nlohmann_json::nlohmann_json)
set_target_properties(stat_bench PROPERTIES VERSION ${PROJECT_VERSION})
target_check_clang_tidy(stat_bench)

find_package(Threads REQUIRED)
target_link_libraries(stat_bench PUBLIC Threads::Threads)

if(MSVC)
    target_compile_options(stat_bench PUBLIC /EHsc /utf-8)
endif()

function(preprocess_template PATH VAR_NAME)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${PATH}" CONTENTS)
    file(
        WRITE "${CMAKE_BINARY_DIR}/include/${PATH}.h"
        "#pragma once\nstatic constexpr const char* ${VAR_NAME} = R\"(${CONTENTS})\";"
    )
endfunction()
preprocess_template(stat_bench/reporter/template/line2d.html line2d)
