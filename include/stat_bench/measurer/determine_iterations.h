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
 * \brief Declaration of determine_iterations function.
 */
#pragma once

#include <cstddef>
#include <string>

#include "stat_bench/bench/benchmark_condition.h"
#include "stat_bench/bench/i_benchmark_case.h"

namespace stat_bench {
namespace measurer {

/*!
 * \brief Determine number of iterations.
 *
 * \param[in] bench_case Case.
 * \param[in] cond Condition.
 * \param[in] measurer_name Measurer name.
 * \param[in] min_sample_duration_sec Minimum duration for a sample. [sec]
 * \return Number of iterations.
 */
[[nodiscard]] auto determine_iterations(bench::IBenchmarkCase* bench_case,
    const bench::BenchmarkCondition& cond, const std::string& measurer_name,
    double min_sample_duration_sec) -> std::size_t;

}  // namespace measurer
}  // namespace stat_bench
