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
 * \brief Definition of ProcessingTimeMeasurer class.
 */
#pragma once

#include <cstddef>
#include <string>

#include "stat_bench/measurer/i_measurer.h"
#include "stat_bench/measurer/measurer_name.h"

namespace stat_bench {
namespace measurer {

/*!
 * \brief Class to measure processing time.
 */
class ProcessingTimeMeasurer final : public IMeasurer {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] samples Number of samples.
     * \param[in] min_warming_up_iterations Minimum number of iterations for
     * warming up.
     * \param[in] min_warming_up_duration_sec Minimum duration for
     * warming up. [sec]
     */
    ProcessingTimeMeasurer(std::size_t samples,
        std::size_t min_warming_up_iterations,
        double min_warming_up_duration_sec)
        : samples_(samples),
          min_warming_up_iterations_(min_warming_up_iterations),
          min_warming_up_duration_sec_(min_warming_up_duration_sec) {}

    //! \copydoc stat_bench::measurer::IMeasurer::name
    [[nodiscard]] auto name() const noexcept -> const MeasurerName& override {
        return name_;
    }

    //! \copydoc stat_bench::measurer::IMeasurer::measure
    [[nodiscard]] auto measure(bench_impl::IBenchmarkCase* bench_case,
        const BenchmarkCondition& cond) const -> Measurement override;

    ProcessingTimeMeasurer(const ProcessingTimeMeasurer&) = delete;
    ProcessingTimeMeasurer(ProcessingTimeMeasurer&&) = delete;
    auto operator=(const ProcessingTimeMeasurer&)
        -> ProcessingTimeMeasurer& = delete;
    auto operator=(ProcessingTimeMeasurer&&)
        -> ProcessingTimeMeasurer& = delete;

    /*!
     * \brief Destructor.
     */
    ~ProcessingTimeMeasurer() override = default;

private:
    //! Name.
    const MeasurerName name_{"Processing Time"};

    //! Number of samples.
    std::size_t samples_;

    //! Minimum number of iterations for warming up.
    std::size_t min_warming_up_iterations_;

    //! Minimum duration for warming up. [sec]
    double min_warming_up_duration_sec_;
};

}  // namespace measurer
}  // namespace stat_bench
