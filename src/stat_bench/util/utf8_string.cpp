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

#include <simdutf.h>

#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace util {

Utf8String::Utf8String(std::string str) : str_(std::move(str)) {
    if (!simdutf::validate_utf8(str_.data(), str_.size())) {
        throw StatBenchException("Invalid UTF-8 string.");
    }
}

auto Utf8String::str() const noexcept -> const std::string& { return str_; }

auto operator<<(std::ostream& stream, const Utf8String& val) -> std::ostream& {
    return stream << val.str();
}

}  // namespace util
}  // namespace stat_bench
