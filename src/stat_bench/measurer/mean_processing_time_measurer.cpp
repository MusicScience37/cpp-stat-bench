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

#include <cstddef>

#include "stat_bench/measurer/determine_iterations.h"
#include "stat_bench/measurer/determine_warming_up_samples.h"
#include "stat_bench/measurer/measure_once.h"

namespace stat_bench {
namespace measurer {

auto MeanProcessingTimeMeasurer::measure(bench_impl::IBenchmarkCase* bench_case,
    const BenchmarkCondition& cond) const -> Measurement {
    const std::size_t iterations =
        determine_iterations(bench_case, cond, name_, min_sample_duration_sec_);

    const std::size_t warming_up_samples =
        determine_warming_up_samples(bench_case, cond, name_, iterations,
            min_warming_up_iterations_, min_warming_up_duration_sec_);

    return measure_once(
        bench_case, cond, name_, iterations, samples_, warming_up_samples);
}

}  // namespace measurer
}  // namespace stat_bench
