#[[
MIT License

Copyright (c) 2020 Kenta Kabashima

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
]]
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "export compile commands" FORCE)

find_program(CLANG_TIDY_PATH clang-tidy)

string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
option(${UPPER_PROJECT_NAME}_ENABLE_CLANG_TIDY "enable clang-tidy" OFF)

set(COMPILE_COMMANDS_PATH "${CMAKE_BINARY_DIR}/compile_commands.json")

# target for clang-tidy of all targets
add_custom_target(${PROJECT_NAME}_clang_tidy ALL)
# set directory for output
set(${UPPER_PROJECT_NAME}_CLANG_TIDY_RESULTS_DIR
    "${CMAKE_BINARY_DIR}/clang_tidy")
file(MAKE_DIRECTORY ${${UPPER_PROJECT_NAME}_CLANG_TIDY_RESULTS_DIR})

# Function target_check_clang_tidy
#
# add a check with clang-tidy to a target
#
function(target_check_clang_tidy _TARGET)
    if(${UPPER_PROJECT_NAME}_ENABLE_CLANG_TIDY)
        if(CLANG_TIDY_PATH)
            # target name
            set(CLANG_TIDY_TARGET "${_TARGET}_clang_tidy")
            if("${_TARGET}" STREQUAL "${PROJECT_NAME}")
                set(CLANG_TIDY_TARGET "${PROJECT_NAME}_${_TARGET}_clang_tidy")
            endif()
            # make the list of source codes
            get_target_property(TARGET_SOURCES ${_TARGET} SOURCES)
            list(FILTER TARGET_SOURCES INCLUDE REGEX ".[cpp|h]$")
            # make a direcotory to output results
            set(OUTPUT_DIR
                "${${UPPER_PROJECT_NAME}_CLANG_TIDY_RESULTS_DIR}/${_TARGET}")
            file(MAKE_DIRECTORY ${OUTPUT_DIR})

            # check the all file
            foreach(SOURCE IN LISTS TARGET_SOURCES)
                # file name of results
                get_filename_component(SOURCE_NAME ${SOURCE} NAME)
                set(RESULT_PATH "${OUTPUT_DIR}/${SOURCE_NAME}.txt")
                if(WIN32)
                    # command to execute clang-tidy
                    add_custom_command(
                        OUTPUT ${RESULT_PATH}
                        COMMAND ${CLANG_TIDY_TEE_BAT_PATH} ${CMAKE_BINARY_DIR}
                                ${SOURCE} ${RESULT_PATH}
                        DEPENDS ${SOURCE}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        COMMENT "Checking ${SOURCE} with clang-tidy")
                else()
                    # command to execute clang-tidy
                    add_custom_command(
                        OUTPUT ${RESULT_PATH}
                        COMMAND
                            "${CLANG_TIDY_PATH}" "-config=" "--quiet"
                            "-p=${CMAKE_BINARY_DIR}" ${SOURCE} | tee
                            ${RESULT_PATH}
                        DEPENDS ${SOURCE}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        COMMENT "Checking ${SOURCE} with clang-tidy")
                endif()
                list(APPEND RESULT_LIST ${RESULT_PATH})
            endforeach()

            # command to show the result of clang-tidy
            add_custom_target(
                ${CLANG_TIDY_TARGET}
                DEPENDS ${RESULT_LIST}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Checked sources in ${_TARGET} with clang-tidy")
            # add dependencies
            add_dependencies(${_TARGET} ${CLANG_TIDY_TARGET})
            add_dependencies(${PROJECT_NAME}_clang_tidy ${CLANG_TIDY_TARGET})
        endif()
    endif()
endfunction()
