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
 * \brief Definition of render_template function.
 */
#include "stat_bench/reporter/render_template.h"

// IWYU pragma: no_include  <stddef.h>
#include <cstddef>
#include <utility>

namespace stat_bench {
namespace reporter {

auto render_template(std::string template_str,
    const std::unordered_map<std::string, std::string>& params) -> std::string {
    std::string contents = std::move(template_str);
    for (const auto& pair : params) {
        const auto& before = pair.first;
        const auto& after = pair.second;
        std::size_t pos = 0;
        while ((pos = contents.find(before, pos)) != std::string::npos) {
            contents.replace(pos, before.size(), after);
            pos += after.size();
        }
    }
    return contents;
}

}  // namespace reporter
}  // namespace stat_bench
