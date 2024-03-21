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
 * \brief Definition of read_file function.
 */
#pragma once

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

#include <fmt/core.h>

namespace stat_bench_test {

/*!
 * \brief Read a file.
 *
 * \param[in] filepath Filepath.
 * \return Contents of the file.
 */
[[nodiscard]] inline auto read_file(const std::string& filepath) {
    std::ifstream stream(filepath);
    if (!stream) {
        throw std::runtime_error(fmt::format("Failed to open {}", filepath));
    }
    return std::string(std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>());
}

/*!
 * \brief Read a binary file.
 *
 * \param[in] filepath Filepath.
 * \return Contents of the file.
 */
[[nodiscard]] inline auto read_binary_file(const std::string& filepath) {
    std::ifstream stream(filepath, std::ios::binary);
    if (!stream) {
        throw std::runtime_error(fmt::format("Failed to open {}", filepath));
    }
    return std::string(std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>());
}

}  // namespace stat_bench_test
