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

#include <filesystem>

namespace stat_bench::util {

void prepare_directory(const std::string& path) {
    std::filesystem::create_directories(path);
}

void prepare_directory_for(const std::string& path) {
    const auto parent =
        std::filesystem::absolute(std::filesystem::path(path)).parent_path();
    prepare_directory(parent.string());
}

}  // namespace stat_bench::util
