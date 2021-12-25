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

namespace stat_bench {
namespace measurer {

auto ProcessingTimeMeasurer::measure(bench::IBenchmarkCase* bench_case,
    const bench::BenchmarkCondition& cond) const -> Measurement {
    constexpr std::size_t iterations = 1;
    bench::InvocationContext context{cond, iterations, samples_};
    bench_case->execute(context);
    if (context.durations().empty()) {
        throw std::runtime_error("No measurement was done.");
    }
    return Measurement(bench_case->info(), cond, name_, iterations, samples_,
        context.durations());
}

}  // namespace measurer
}  // namespace stat_bench
