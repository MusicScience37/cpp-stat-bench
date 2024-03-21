/*
 * Copyright 2021 MusicScience37 (Kenta Kabashima)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * \file
 * \brief Definition of prepare_directory function.
 */
#include "stat_bench/util/prepare_directory.h"

#include <cstddef>

#ifdef _WIN32

#include <Windows.h>  // GetFileAttributesA
#include <direct.h>   // _mkdir
#include <fileapi.h>  // GetFileAttributesA

namespace stat_bench {
namespace util {

[[nodiscard]] static auto path_exists(const std::string& path) -> bool {
    return ::GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

void prepare_directory(const std::string& path) {
    if (path_exists(path)) {
        return;
    }

    std::size_t pos = 0;
    while (true) {
        pos = path.find_first_of("/\\", pos);
        if (pos == std::string::npos) {
            pos = path.size();
        }
        const auto parent = path.substr(0, pos);
        ++pos;

        if (parent.empty() || path_exists(parent)) {
            continue;
        }
        ::_mkdir(parent.c_str());
        if (pos >= path.size()) {
            return;
        }
    }
}

void prepare_directory_for(const std::string& path) {
    const std::size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return;
    }
    prepare_directory(path.substr(0, pos));
}

}  // namespace util
}  // namespace stat_bench

#else

#include <sys/stat.h>  // mkdir, stat
#include <sys/types.h>

namespace stat_bench {
namespace util {

[[nodiscard]] static auto path_exists(const std::string& path) -> bool {
    struct stat buf {};
    return ::stat(path.c_str(), &buf) == 0;
}

void prepare_directory(const std::string& path) {
    if (path_exists(path)) {
        return;
    }

    std::size_t pos = 0;
    while (true) {
        pos = path.find_first_of('/', pos);
        if (pos == std::string::npos) {
            pos = path.size();
        }
        const auto parent = path.substr(0, pos);
        ++pos;

        if (parent.empty() || path_exists(parent)) {
            continue;
        }
        // NOLINTNEXTLINE(google-readability-casting): This is constructor.
        const auto mode = ::mode_t(0755);
        ::mkdir(parent.c_str(), mode);
        if (pos >= path.size()) {
            return;
        }
    }
}

void prepare_directory_for(const std::string& path) {
    const std::size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) {
        return;
    }
    prepare_directory(path.substr(0, pos));
}

}  // namespace util
}  // namespace stat_bench

#endif
