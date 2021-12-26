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
 * \brief Definition of calc_stat function.
 */
#include "stat_bench/stat/calc_stat.h"

#include <stdexcept>

namespace stat_bench {
namespace stat {

auto calc_stat(const std::vector<std::vector<clock::Duration>>& durations,
    std::size_t iterations) -> stat::Statistics {
    if (durations.empty() || durations.at(0).empty()) {
        throw std::invalid_argument("No duration sample for statistics.");
    }

    stat::Statistics stat;
    stat.reserve(durations.size() * durations.at(0).size());
    const double inv_iterations = 1.0 / static_cast<double>(iterations);
    for (const auto& durations_per_thread : durations) {
        for (const auto& duration : durations_per_thread) {
            stat.add(duration.seconds() * inv_iterations);
        }
    }
    stat.calc();

    return stat;
}

auto calc_stat(const std::vector<std::vector<double>>& values)
    -> stat::Statistics {
    if (values.empty() || values.at(0).empty()) {
        throw std::invalid_argument("No sample value for statistics.");
    }

    stat::Statistics stat;
    stat.reserve(values.size() * values.at(0).size());
    for (const auto& values_per_thread : values) {
        for (double value : values_per_thread) {
            stat.add(value);
        }
    }
    stat.calc();

    return stat;
}

}  // namespace stat
}  // namespace stat_bench
