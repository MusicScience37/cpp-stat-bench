/*
 * Copyright 2024 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of ParameterDict class.
 */
#include "stat_bench/param/parameter_dict.h"

#include <utility>

#include <fmt/format.h>

namespace stat_bench {
namespace param {

ParameterDict::ParameterDict(
    std::unordered_map<std::string, ParameterValue> data)
    : data_(std::move(data)) {}

auto ParameterDict::has(const std::string& param_name) const -> bool {
    return data_.count(param_name) == 1;
}

auto ParameterDict::format_to(fmt::format_context::iterator out) const
    -> fmt::format_context::iterator {
    // Sort keys.
    std::set<std::string> keys;
    for (const auto& pair : data_) {
        keys.insert(pair.first);
    }

    bool is_first = true;
    for (const auto& key : keys) {
        if (is_first) {
            is_first = false;
        } else {
            *out = ',';
            ++out;
            *out = ' ';
            ++out;
        }
        out = fmt::format_to(out, "{}={}", key, data_.at(key).to_string());
    }

    return out;
}

auto ParameterDict::as_string_dict() const
    -> std::unordered_map<std::string, std::string> {
    std::unordered_map<std::string, std::string> data;
    data.reserve(data_.size());
    for (const auto& pair : data_) {
        data.emplace(pair.first, pair.second.to_string());
    }
    return data;
}

}  // namespace param
}  // namespace stat_bench

namespace fmt {

auto formatter<stat_bench::param::ParameterDict>::format(
    const stat_bench::param::ParameterDict& val, format_context& context) ->
    typename format_context::iterator {
    return val.format_to(context.out());
}

}  // namespace fmt
