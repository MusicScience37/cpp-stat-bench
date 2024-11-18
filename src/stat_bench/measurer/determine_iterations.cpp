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
 * \brief Definition of determine_iterations function.
 */
#include "stat_bench/measurer/determine_iterations.h"

#include <algorithm>  // std::min, std::max
#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/measurer/measure_once.h"
#include "stat_bench/measurer/measurement.h"

namespace stat_bench {
namespace measurer {

auto determine_iterations(bench_impl::IBenchmarkCase* bench_case,
    const BenchmarkCondition& cond, const MeasurerName& measurer_name,
    double min_sample_duration_sec) -> std::size_t {
    std::size_t iterations = 1;
    constexpr std::size_t trials = 10;
    for (std::size_t i = 0; i < trials; ++i) {
        constexpr std::size_t samples = 2;
        const auto data = measure_once(
            bench_case, cond, measurer_name, iterations, samples, 0);
        const double duration_sec = data.durations().at(0).at(1).seconds();
        if (duration_sec > min_sample_duration_sec) {
            break;
        }

        const double multiplier =
            std::min(
                min_sample_duration_sec / std::max(duration_sec, 1e-9), 10.0) *
            1.2;
        constexpr double max_iterations = 1e+6;
        iterations = static_cast<std::size_t>(std::min(
            max_iterations, static_cast<double>(iterations) * multiplier));
    }
    return iterations;
}

}  // namespace measurer
}  // namespace stat_bench
