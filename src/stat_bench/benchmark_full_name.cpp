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
 * \brief Implementation of BenchmarkFullName class.
 */
#include "stat_bench/benchmark_full_name.h"

#include <fmt/format.h>

namespace fmt {

auto formatter<stat_bench::BenchmarkFullName>::format(
    const stat_bench::BenchmarkFullName& val, format_context& context) const
    -> format_context::iterator {
    return formatter<string_view>::format(
        fmt::format("{}/{}", val.group_name(), val.case_name()), context);
}

}  // namespace fmt
