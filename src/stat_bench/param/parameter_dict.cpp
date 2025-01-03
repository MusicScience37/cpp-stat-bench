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

#include <set>
#include <utility>

#include <fmt/format.h>  // IWYU pragma: keep

#include "stat_bench/param/parameter_name.h"

namespace stat_bench {
namespace param {

ParameterDict::ParameterDict(
    std::unordered_map<ParameterName, ParameterValue> data)
    : data_(std::move(data)) {}

auto ParameterDict::empty() const noexcept -> bool { return data_.empty(); }

auto ParameterDict::has(const ParameterName& param_name) const -> bool {
    return data_.count(param_name) == 1;
}

auto ParameterDict::get_as_double(const ParameterName& param_name) const
    -> double {
    const auto iter = data_.find(param_name);
    if (iter == data_.end()) {
        throw StatBenchException(
            fmt::format("Parameter {} not found.", param_name));
    }
    return iter->second.to_double();
}

auto ParameterDict::format_to(fmt::format_context::iterator out) const
    -> fmt::format_context::iterator {
    // Sort keys.
    std::set<ParameterName> keys;
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
    -> std::unordered_map<util::Utf8String, util::Utf8String> {
    std::unordered_map<util::Utf8String, util::Utf8String> data;
    data.reserve(data_.size());
    for (const auto& pair : data_) {
        data.emplace(pair.first.str(), pair.second.to_string());
    }
    return data;
}

auto ParameterDict::calculate_hash() const -> std::size_t {
    std::size_t hash = 0;
    std::hash<ParameterName> name_hash{};
    for (const auto& pair : data_) {
        hash ^= name_hash(pair.first);
        hash ^= pair.second.calculate_hash();
    }
    return hash;
}

auto ParameterDict::operator==(const ParameterDict& rhs) const -> bool {
    return data_ == rhs.data_;
}

auto ParameterDict::operator!=(const ParameterDict& rhs) const -> bool {
    return !(*this == rhs);
}

}  // namespace param
}  // namespace stat_bench

namespace fmt {

auto formatter<stat_bench::param::ParameterDict>::format(
    const stat_bench::param::ParameterDict& val, format_context& context) const
    -> typename format_context::iterator {
    return val.format_to(context.out());
}

}  // namespace fmt
