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
 * \brief Definition of measure_once function.
 */
#include "stat_bench/measurer/measure_once.h"

#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/bench_impl/invocation_context_registry.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/custom_output_name.h"
#include "stat_bench/invocation_context.h"
#include "stat_bench/measurer/measurement.h"

namespace stat_bench {
namespace measurer {

auto measure_once(bench_impl::IBenchmarkCase* bench_case,
    const BenchmarkCondition& cond, const MeasurerName& measurer_name,
    std::size_t iterations, std::size_t samples, std::size_t warming_up_samples)
    -> Measurement {
    auto& context = bench_impl::InvocationContextRegistry::instance().create(
        cond, iterations, samples + warming_up_samples, warming_up_samples);
    bench_case->execute();
    if (context.durations().empty()) {
        throw std::runtime_error("No measurement was done.");
    }
    auto measurement = Measurement{bench_case->info(), cond, measurer_name,
        iterations, samples, context.durations(), context.custom_stat_outputs(),
        context.custom_outputs()};

    stat_bench::bench_impl::InvocationContextRegistry::instance().clear();

    return measurement;
}

}  // namespace measurer
}  // namespace stat_bench
