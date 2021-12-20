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
     */
    explicit MeanProcessingTimeMeasurer(
        double min_sample_duration_sec, std::size_t samples)
        : min_sample_duration_sec_(min_sample_duration_sec),
          samples_(samples) {}

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
    /*!
     * \brief Measure once.
     *
     * \param[in] bench_case Case.
     * \param[in] cond Condition.
     * \param[in] iterations Number of iterations.
     * \param[in] samples Number of samples.
     * \return
     */
    [[nodiscard]] auto measure_once(bench::IBenchmarkCase* bench_case,
        const bench::BenchmarkCondition& cond, std::size_t iterations,
        std::size_t samples) const -> Measurement;

    //! Name.
    const std::string name_{"Mean Processing Time"};

    //! Minimum duration for a sample. [sec]
    double min_sample_duration_sec_;

    //! Number of samples.
    std::size_t samples_;
};

}  // namespace measurer
}  // namespace stat_bench
