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
 * \brief Implementation of RegexFilter class.
 */
#include "stat_bench/filters/regex_filter.h"

#include <regex>

namespace stat_bench {
namespace filters {

RegexFilter::RegexFilter(const std::string& regex)
    : regex_(regex,
          std::regex_constants::ECMAScript | std::regex_constants::optimize) {}

auto RegexFilter::check(const bench::BenchmarkFullName& name) const -> bool {
    return std::regex_match(fmt::format("{}", name), regex_);
}

}  // namespace filters
}  // namespace stat_bench
