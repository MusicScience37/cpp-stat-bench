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

#include <cstdint>
#include <string>
#include <string_view>

namespace stat_bench {
namespace util {

auto escape_for_file_name(const Utf8String& input) -> Utf8String {
    std::string output;
    for (const char c : input.str()) {
        // TODO check if the character is valid for a file name
        if (c <= ' ' || c == '"' || c == '#' || c == '$' || c == '%' ||
            c == '&' || c == '*' || c == '+' || c == ',' || c == '/' ||
            c == ':' || c == ';' || c == '<' || c == '=' || c == '>' ||
            c == '?' || c == '@' || c == '[' || c == '^' || c == '`' ||
            c == '{' || c == '|' || c == '}' || c > '~') {
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
