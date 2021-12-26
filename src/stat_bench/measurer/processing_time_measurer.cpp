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
 * \brief Implementation of ProcessingTimeMeasurer class.
 */
#include "stat_bench/measurer/processing_time_measurer.h"

#include <stdexcept>

#include "stat_bench/bench/invocation_context.h"
#include "stat_bench/measurer/measure_once.h"

namespace stat_bench {
namespace measurer {

auto ProcessingTimeMeasurer::measure(bench::IBenchmarkCase* bench_case,
    const bench::BenchmarkCondition& cond) const -> Measurement {
    // TODO warming up
    constexpr std::size_t iterations = 1;
    return measure_once(bench_case, cond, name_, iterations, samples_, 0);
}

}  // namespace measurer
}  // namespace stat_bench
