/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of Measurer class.
 */
#include "stat_bench/measurer/measurer.h"

#include "stat_bench/measurer/determine_iterations.h"
#include "stat_bench/measurer/determine_warming_up_samples.h"
#include "stat_bench/measurer/measure_once.h"

namespace stat_bench {
namespace measurer {

Measurer::Measurer(double min_sample_duration_sec,
    double min_warming_up_duration_sec, std::size_t samples,
    std::size_t min_warming_up_iterations)
    : min_sample_duration_sec_(min_sample_duration_sec),
      min_warming_up_duration_sec_(min_warming_up_duration_sec),
      samples_(samples),
      min_warming_up_iterations_(min_warming_up_iterations) {}

auto Measurer::measure(bench_impl::IBenchmarkCase* bench_case,
    const BenchmarkCondition& condition, const MeasurementConfig& config) const
    -> Measurement {
    const std::size_t samples = config.samples().value_or(samples_);

    std::size_t iterations;
    if (config.iterations().has_value()) {
        iterations = config.iterations().value();
    } else {
        iterations = determine_iterations(
            bench_case, condition, config.type(), min_sample_duration_sec_);
    }

    std::size_t warming_up_samples;
    if (config.warming_up_samples().has_value()) {
        warming_up_samples = config.warming_up_samples().value();
    } else {
        warming_up_samples = determine_warming_up_samples(bench_case, condition,
            config.type(), iterations, min_warming_up_iterations_,
            min_warming_up_duration_sec_);
    }

    return measure_once(bench_case, condition, config.type(), iterations,
        samples, warming_up_samples);
}

}  // namespace measurer
}  // namespace stat_bench
