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
 * \brief Definition of determine_warming_up_samples function.
 */
#include "stat_bench/measurer/determine_warming_up_samples.h"

#include <algorithm>  // std::min, std::max
#include <limits>

#include "stat_bench/measurer/measure_once.h"

namespace stat_bench {
namespace measurer {

auto determine_warming_up_samples(bench::IBenchmarkCase* bench_case,
    const bench::BenchmarkCondition& cond, const std::string& measurer_name,
    std::size_t iterations, std::size_t min_iterations, double min_duration_sec)
    -> std::size_t {
    std::size_t warming_up_samples =
        (min_iterations + iterations - 1) / iterations;
    constexpr std::size_t trials = 10;
    for (std::size_t i = 0; i < trials; ++i) {
        const auto data = measure_once(
            bench_case, cond, measurer_name, iterations, warming_up_samples, 0);
        const double duration_sec = data.durations_stat().mean() *
            static_cast<double>(iterations) *
            static_cast<double>(warming_up_samples);
        if (duration_sec > min_duration_sec) {
            break;
        }

        const double multiplier =
            std::min(min_duration_sec / std::max(duration_sec, 1e-9), 10.0) *
            1.2;
        constexpr double max_iterations = 1e+6;
        const double max_samples =
            max_iterations / static_cast<double>(iterations);
        warming_up_samples = static_cast<std::size_t>(std::min(
            max_samples, static_cast<double>(warming_up_samples) * multiplier));
    }
    return warming_up_samples;
}

}  // namespace measurer
}  // namespace stat_bench
