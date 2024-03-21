/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of GlobFilter class.
 */
#include "stat_bench/filters/glob_filter.h"

#include <utility>

#include <fmt/core.h>

#include "stat_bench/util/check_glob_pattern.h"

namespace stat_bench {
namespace filters {

GlobFilter::GlobFilter(std::string pattern) : pattern_(std::move(pattern)) {}

auto GlobFilter::check(const BenchmarkFullName& name) const -> bool {
    return util::check_glob_pattern(pattern_, fmt::format("{}", name));
}

}  // namespace filters
}  // namespace stat_bench
