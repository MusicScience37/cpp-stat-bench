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

add_library(${PROJECT_NAME}_cpp_warnings INTERFACE)

string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
option(${UPPER_PROJECT_NAME}_ENABLE_CPP_WARNINGS
       "enable compiler warnings of C++" OFF)

if(${UPPER_PROJECT_NAME}_ENABLE_CPP_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME}_cpp_warnings INTERFACE -Wall
                                                                      -Wextra)
    endif()
endif()

if(MSVC)
    target_compile_definitions(${PROJECT_NAME}_cpp_warnings
                               INTERFACE _CRT_SECURE_NO_WARNINGS=1)
endif()
