/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of escape_for_file_name function.
 */
#include "stat_bench/util/escape_for_file_name.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace stat_bench {
namespace util {

namespace {

/*!
 * \brief Characters that are safe for a file name.
 *
 * This is based on a research in doc/sphinx/src/design/escape_file_names.md.
 */
constexpr std::string_view safe_chars =
    "!+-"
    "0123456789"
    "@"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "^_"
    "abcdefghijklmnopqrstuvwxyz"
    "{}~";

//! Number of 8-bit characters.
constexpr std::size_t num_8bit_chars = 256;

/*!
 * \brief Create a table of safe characters.
 *
 * \return Table.
 */
[[nodiscard]] constexpr auto create_safe_char_table()
    -> std::array<bool, num_8bit_chars> {
    std::array<bool, num_8bit_chars> table{};
    for (std::size_t i = 0; i < num_8bit_chars; ++i) {
        table[i] = false;
    }
    for (const char c : safe_chars) {
        table[static_cast<std::uint8_t>(c)] = true;
    }
    return table;
}

/*!
 * \brief Check if a character is safe for a file name.
 *
 * \param[in] c Character.
 * \retval true The character is safe.
 * \retval false The character is not safe.
 */
[[nodiscard]] auto is_safe_char(const char c) -> bool {
    static constexpr auto table = create_safe_char_table();
    return table[static_cast<std::uint8_t>(c)];
}

}  // namespace

auto escape_for_file_name(const Utf8String& input) -> Utf8String {
    std::string output;
    for (const char c : input.str()) {
        // TODO check if the character is valid for a file name
        if (!is_safe_char(c)) {
            output.push_back('%');
            constexpr std::string_view hex_chars = "0123456789ABCDEF";
            const auto byte =
                static_cast<unsigned>(static_cast<std::uint8_t>(c));
            constexpr unsigned mask = 0xFU;
            output.push_back(hex_chars[(byte >> 4U) & mask]);
            output.push_back(hex_chars[byte & mask]);
        } else {
            output.push_back(c);
        }
    }
    return Utf8String(output);
}

}  // namespace util
}  // namespace stat_bench
