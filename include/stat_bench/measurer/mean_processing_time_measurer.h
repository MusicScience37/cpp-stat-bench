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
 * \brief Definition of MeanProcessingTimeMeasurer class.
 */
#pragma once

#include "stat_bench/measurer/i_measurer.h"

namespace stat_bench {
namespace measurer {

/*!
 * \brief Class to measure mean processing time.
 */
class MeanProcessingTimeMeasurer final : public IMeasurer {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] min_sample_duration_sec Minimum duration for a sample. [sec]
     * \param[in] samples Number of samples.
     * \param[in] min_warming_up_iterations Minimum number of iterations for
     * warming up.
     * \param[in] min_warming_up_duration_sec Minimum duration for
     * warming up. [sec]
     */
    MeanProcessingTimeMeasurer(double min_sample_duration_sec,
        std::size_t samples, std::size_t min_warming_up_iterations,
        double min_warming_up_duration_sec)
        : min_sample_duration_sec_(min_sample_duration_sec),
          samples_(samples),
          min_warming_up_iterations_(min_warming_up_iterations),
          min_warming_up_duration_sec_(min_warming_up_duration_sec) {}

    //! \copydoc stat_bench::measurer::IMeasurer::name
    [[nodiscard]] auto name() const noexcept -> const std::string& override {
        return name_;
    }

    //! \copydoc stat_bench::measurer::IMeasurer::measure
    [[nodiscard]] auto measure(bench::IBenchmarkCase* bench_case,
        const bench::BenchmarkCondition& cond) const -> Measurement override;

    MeanProcessingTimeMeasurer(const MeanProcessingTimeMeasurer&) = delete;
    MeanProcessingTimeMeasurer(MeanProcessingTimeMeasurer&&) = delete;
    auto operator=(const MeanProcessingTimeMeasurer&)
        -> MeanProcessingTimeMeasurer& = delete;
    auto operator=(MeanProcessingTimeMeasurer&&)
        -> MeanProcessingTimeMeasurer& = delete;

    /*!
     * \brief Destructor.
     */
    ~MeanProcessingTimeMeasurer() override = default;

private:
    //! Name.
    const std::string name_{"Mean Processing Time"};

    //! Minimum duration for a sample. [sec]
    double min_sample_duration_sec_;

    //! Number of samples.
    std::size_t samples_;

    //! Minimum number of iterations for warming up.
    std::size_t min_warming_up_iterations_;

    //! Minimum duration for warming up. [sec]
    double min_warming_up_duration_sec_;
};

}  // namespace measurer
}  // namespace stat_bench
