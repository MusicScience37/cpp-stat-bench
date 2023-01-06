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

#include "stat_bench/measurer/determine_iterations.h"

namespace stat_bench {
namespace measurer {

auto determine_warming_up_samples(bench_impl::IBenchmarkCase* bench_case,
    const BenchmarkCondition& cond, const std::string& measurer_name,
    std::size_t iterations, std::size_t min_iterations, double min_duration_sec)
    -> std::size_t {
    std::size_t warming_up_iterations =
        determine_iterations(bench_case, cond, measurer_name, min_duration_sec);
    if (warming_up_iterations < min_iterations) {
        warming_up_iterations = min_iterations;
    }
    const std::size_t warming_up_samples =
        (warming_up_iterations + iterations - 1) / iterations;
    return warming_up_samples;
}

}  // namespace measurer
}  // namespace stat_bench
