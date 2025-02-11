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
 * \brief Definition of check_glob_pattern function.
 */
#include "stat_bench/util/check_glob_pattern.h"

#include <cstddef>

#include "stat_bench/util/string_view.h"

namespace stat_bench {
namespace util {

namespace {

[[nodiscard]] auto check_glob_pattern_impl_asterisk(
    StringView pattern, StringView str) -> bool {
    const StringView remaining_pattern = pattern.substr(1U);
    for (std::size_t size = 0; size < str.size(); ++size) {
        if (check_glob_pattern(remaining_pattern, str.substr(size))) {
            return true;
        }
    }
    return check_glob_pattern(remaining_pattern, StringView());
}

}  // namespace

auto check_glob_pattern(StringView pattern, StringView str) -> bool {
    std::size_t pattern_index = 0;
    std::size_t str_index = 0;
    while (true) {
        if (pattern_index >= pattern.size()) {
            return str_index == str.size();
        }

        if (pattern.at(pattern_index) == '*') {
            return check_glob_pattern_impl_asterisk(
                pattern.substr(pattern_index), str.substr(str_index));
        }

        if (str_index >= str.size()) {
            return false;
        }

        if (pattern.at(pattern_index) != str.at(str_index)) {
            return false;
        }

        ++pattern_index;
        ++str_index;
    }
}

}  // namespace util
}  // namespace stat_bench
