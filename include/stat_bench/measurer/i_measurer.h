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
 * \brief Definition of IMeasurer class.
 */
#pragma once

#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurement_type.h"

namespace stat_bench {
namespace measurer {

/*!
 * \brief Interface of measurers of durations.
 */
class IMeasurer {
public:
    /*!
     * \brief Get the measurement type of this measurer.
     *
     * \return Name.
     */
    [[nodiscard]] virtual auto type() const noexcept
        -> const MeasurementType& = 0;

    /*!
     * \brief Measure durations.
     *
     * \param[in] bench_case Case.
     * \param[in] cond Condition.
     * \return Result.
     */
    [[nodiscard]] virtual auto measure(bench_impl::IBenchmarkCase* bench_case,
        const BenchmarkCondition& cond) const -> Measurement = 0;

    IMeasurer(const IMeasurer&) = delete;
    IMeasurer(IMeasurer&&) = delete;
    auto operator=(const IMeasurer&) -> IMeasurer& = delete;
    auto operator=(IMeasurer&&) -> IMeasurer& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~IMeasurer() = default;

protected:
    /*!
     * \brief Constructor.
     */
    IMeasurer() = default;
};

}  // namespace measurer
}  // namespace stat_bench
