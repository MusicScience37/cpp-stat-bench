#[[
MIT License

Copyright (c) 2023 Kenta Kabashima

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
function(parse_version VERSION_FILE VARIABLE_PREFIX)
    file(READ ${VERSION_FILE} CONTENTS)

    string(REGEX MATCH "${VARIABLE_PREFIX}_VERSION_MAJOR ([0-9]+)" _
                 ${CONTENTS})
    set(${VARIABLE_PREFIX}_VERSION_MAJOR
        ${CMAKE_MATCH_1}
        CACHE STRING "Major version" FORCE)

    string(REGEX MATCH "${VARIABLE_PREFIX}_VERSION_MINOR ([0-9]+)" _
                 ${CONTENTS})
    set(${VARIABLE_PREFIX}_VERSION_MINOR
        ${CMAKE_MATCH_1}
        CACHE STRING "Minor version" FORCE)

    string(REGEX MATCH "${VARIABLE_PREFIX}_VERSION_PATCH ([0-9]+)" _
                 ${CONTENTS})
    set(${VARIABLE_PREFIX}_VERSION_PATCH
        ${CMAKE_MATCH_1}
        CACHE STRING "Patch version" FORCE)

    set(${VARIABLE_PREFIX}_VERSION
        "${${VARIABLE_PREFIX}_VERSION_MAJOR}.${${VARIABLE_PREFIX}_VERSION_MINOR}.${${VARIABLE_PREFIX}_VERSION_PATCH}"
        CACHE STRING "Version" FORCE)
endfunction()
