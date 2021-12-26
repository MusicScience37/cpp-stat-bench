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
 * \brief Implementation of MeanDurationMeasurer class.
 */
#include "stat_bench/measurer/mean_processing_time_measurer.h"

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>

#include "stat_bench/bench/invocation_context.h"
#include "stat_bench/measurer/measure_once.h"

namespace stat_bench {
namespace measurer {

auto MeanProcessingTimeMeasurer::measure(bench::IBenchmarkCase* bench_case,
    const bench::BenchmarkCondition& cond) const -> Measurement {
    // TODO warming up

    // First find the proper number of iterations.
    std::size_t iterations = 1;
    constexpr std::size_t trials = 10;
    for (std::size_t i = 0; i < trials; ++i) {
        constexpr std::size_t samples = 1;
        const auto data =
            measure_once(bench_case, cond, name_, iterations, samples, 0);
        const double duration_sec =
            data.durations_stat().mean() * static_cast<double>(iterations);
        if (duration_sec > min_sample_duration_sec_) {
            break;
        }

        const double multiplier = std::min(
            min_sample_duration_sec_ / std::max(duration_sec, 1e-9), 100.0);
        constexpr double max_iterations = 1e+6;
        iterations = static_cast<std::size_t>(std::min(
            max_iterations, static_cast<double>(iterations) * multiplier));
    }

    return measure_once(bench_case, cond, name_, iterations, samples_, 0);
}

}  // namespace measurer
}  // namespace stat_bench
