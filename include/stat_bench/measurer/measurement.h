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
 * \brief Definition of Measurement class.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "stat_bench/bench/benchmark_case_info.h"
#include "stat_bench/bench/benchmark_condition.h"
#include "stat_bench/clock/duration.h"

namespace stat_bench {
namespace measurer {

/*!
 * \brief Class of data of measurements.
 */
class Measurement {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] case_info Information of the case.
     * \param[in] cond Condition.
     * \param[in] measurer_name Name of the measurer.
     * \param[in] iterations Number of iterations.
     * \param[in] samples Number of samples.
     * \param[in] durations Measured durations.
     */
    Measurement(bench::BenchmarkCaseInfo case_info,
        bench::BenchmarkCondition cond, std::string measurer_name,
        std::size_t iterations, std::size_t samples,
        std::vector<std::vector<clock::Duration>> durations)
        : case_info_(std::move(case_info)),
          cond_(cond),
          measurer_name_(std::move(measurer_name)),
          iterations_(iterations),
          samples_(samples),
          durations_(std::move(durations)) {}

    /*!
     * \brief Get the information of the case.
     *
     * \return Information of the case.
     */
    [[nodiscard]] auto case_info() const noexcept
        -> const bench::BenchmarkCaseInfo& {
        return case_info_;
    }

    /*!
     * \brief Get the condition.
     *
     * \return Condition.
     */
    [[nodiscard]] auto cond() const noexcept
        -> const bench::BenchmarkCondition& {
        return cond_;
    }

    /*!
     * \brief Get the name of the measurer.
     *
     * \return Name of the measurer.
     */
    [[nodiscard]] auto measurer_name() const noexcept -> const std::string& {
        return measurer_name_;
    }

    /*!
     * \brief Get the number of iterations.
     *
     * \return Number of iterations.
     */
    [[nodiscard]] auto iterations() const noexcept -> const std::size_t& {
        return iterations_;
    }

    /*!
     * \brief Get the number of samples.
     *
     * \return Number of samples.
     */
    [[nodiscard]] auto samples() const noexcept -> const std::size_t& {
        return samples_;
    }

    /*!
     * \brief Get the measured durations.
     *
     * \return Measured durations.
     */
    [[nodiscard]] auto durations() const noexcept
        -> const std::vector<std::vector<clock::Duration>>& {
        return durations_;
    }

private:
    //! Information of the case.
    bench::BenchmarkCaseInfo case_info_;

    //! Condition.
    bench::BenchmarkCondition cond_;

    //! Name of the measurer.
    std::string measurer_name_;

    //! Number of iterations.
    std::size_t iterations_;

    //! Number of samples.
    std::size_t samples_;

    //! Measured durations.
    std::vector<std::vector<clock::Duration>> durations_;
};

}  // namespace measurer
}  // namespace stat_bench
