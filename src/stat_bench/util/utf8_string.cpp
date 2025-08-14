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
 * \brief Implementation of Utf8String class.
 */
#include "stat_bench/util/utf8_string.h"

#include <ostream>
#include <utility>

#include <fmt/format.h>
#include <simdutf.h>

#include "stat_bench/stat_bench_exception.h"

namespace stat_bench::util {

Utf8String::Utf8String(std::string str) : str_(std::move(str)) {
    if (!simdutf::validate_utf8(str_.data(), str_.size())) {
        throw StatBenchException("Invalid UTF-8 string.");
    }
}

auto Utf8String::str() const noexcept -> const std::string& { return str_; }

auto operator==(const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool {
    return lhs.str() == rhs.str();
}

auto operator!=(const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool {
    return !(lhs == rhs);
}

auto operator<(const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool {
    return lhs.str() < rhs.str();
}

auto operator>(const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool {
    return rhs < lhs;
}

auto operator<=(const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool {
    return !(rhs < lhs);
}

auto operator>=(const Utf8String& lhs, const Utf8String& rhs) noexcept -> bool {
    return !(lhs < rhs);
}

}  // namespace stat_bench::util

namespace fmt {

auto formatter<stat_bench::util::Utf8String>::format(
    const stat_bench::util::Utf8String& val, format_context& context) const
    -> format_context::iterator {
    return formatter<string_view>::format(val.str(), context);
}

}  // namespace fmt

namespace stat_bench::util {

auto operator<<(std::ostream& stream, const Utf8String& val) -> std::ostream& {
    return stream << val.str();
}

}  // namespace stat_bench::util
