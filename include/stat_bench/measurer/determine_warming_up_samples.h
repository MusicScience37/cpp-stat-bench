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
 * \brief Declaration of determine_warming_up_samples function.
 */
#pragma once

#include <cstddef>

#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/measurer/measurement_type.h"

namespace stat_bench::measurer {

/*!
 * \brief Determine number of iterations.
 *
 * \param[in] bench_case Case.
 * \param[in] cond Condition.
 * \param[in] measurement_type Measurement type.
 * \param[in] iterations Number of iterations.
 * \param[in] min_iterations Minimum number of iterations for warming up.
 * \param[in] min_duration_sec Minimum duration for warming up. [sec]
 * \return Number of samples for warming up.
 */
[[nodiscard]] auto determine_warming_up_samples(
    bench_impl::IBenchmarkCase* bench_case, const BenchmarkCondition& cond,
    const MeasurementType& measurement_type, std::size_t iterations,
    std::size_t min_iterations, double min_duration_sec) -> std::size_t;

}  // namespace stat_bench::measurer
