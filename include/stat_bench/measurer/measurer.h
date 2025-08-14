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
 * \brief Definition of Measurer class.
 */
#pragma once

#include <cstddef>

#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/measurement_config.h"
#include "stat_bench/measurer/measurement.h"

namespace stat_bench::measurer {

/*!
 * \brief Class to measure durations.
 */
class Measurer {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] min_sample_duration_sec Minimum duration for a sample. [sec]
     * \param[in] min_warming_up_duration_sec Minimum duration for warming up.
     * [sec]
     * \param[in] samples Number of samples.
     * \param[in] min_warming_up_iterations Minimum number of iterations for
     * warming up.
     */
    Measurer(double min_sample_duration_sec, double min_warming_up_duration_sec,
        std::size_t samples, std::size_t min_warming_up_iterations);

    /*!
     * \brief Measure durations.
     *
     * \param[in] bench_case Case.
     * \param[in] condition Conditions.
     * \param[in] config Measurement configuration.
     * \return Result.
     */
    [[nodiscard]] auto measure(bench_impl::IBenchmarkCase* bench_case,
        const BenchmarkCondition& condition,
        const MeasurementConfig& config) const -> Measurement;

private:
    //! Minimum duration for a sample. [sec]
    double min_sample_duration_sec_;

    //! Minimum duration for warming up. [sec]
    double min_warming_up_duration_sec_;

    //! Number of samples.
    std::size_t samples_;

    //! Minimum number of iterations for warming up.
    std::size_t min_warming_up_iterations_;
};

}  // namespace stat_bench::measurer
