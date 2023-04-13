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

// IWYU pragma: no_include <stddef.h>
// IWYU pragma: no_include <type_traits>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/stat/calc_stat.h"
#include "stat_bench/stat/custom_stat_output.h"
#include "stat_bench/stat/statistics.h"

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
     * \param[in] custom_stat_outputs Custom outputs with statistics.
     * \param[in] custom_outputs Custom outputs without statistics.
     */
    Measurement(BenchmarkFullName case_info, BenchmarkCondition cond,
        std::string measurer_name, std::size_t iterations, std::size_t samples,
        std::vector<std::vector<clock::Duration>> durations,
        std::vector<std::shared_ptr<stat::CustomStatOutput>>
            custom_stat_outputs,
        std::vector<std::pair<std::string, double>> custom_outputs)
        : case_info_(std::move(case_info)),
          cond_(std::move(cond)),
          measurer_name_(std::move(measurer_name)),
          iterations_(iterations),
          samples_(samples),
          durations_(std::move(durations)),
          durations_stat_(stat::calc_stat(durations_, iterations)),
          custom_stat_outputs_(std::move(custom_stat_outputs)),
          custom_outputs_(std::move(custom_outputs)) {
        custom_stat_.reserve(custom_stat_outputs_.size());
        for (const auto& out : custom_stat_outputs_) {
            out->preprocess(durations_);
            custom_stat_.push_back(out->stat());
        }
    }

    /*!
     * \brief Get the information of the case.
     *
     * \return Information of the case.
     */
    [[nodiscard]] auto case_info() const noexcept -> const BenchmarkFullName& {
        return case_info_;
    }

    /*!
     * \brief Get the condition.
     *
     * \return Condition.
     */
    [[nodiscard]] auto cond() const noexcept -> const BenchmarkCondition& {
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
     * \note Duration of iterations in each sample is measured per thread.
     *
     * \return Measured durations.
     */
    [[nodiscard]] auto durations() const noexcept
        -> const std::vector<std::vector<clock::Duration>>& {
        return durations_;
    }

    /*!
     * \brief Get the statistics of durations.
     *
     * \return Statistics of durations.
     */
    [[nodiscard]] auto durations_stat() const noexcept
        -> const stat::Statistics& {
        return durations_stat_;
    }

    /*!
     * \brief Get the custom outputs with statistics.
     *
     * \return Custom outputs with statistics.
     */
    [[nodiscard]] auto custom_stat_outputs() const noexcept
        -> const std::vector<std::shared_ptr<stat::CustomStatOutput>>& {
        return custom_stat_outputs_;
    }

    /*!
     * \brief Get the statistics of custom outputs.
     *
     * \return Statistics of custom outputs.
     */
    [[nodiscard]] auto custom_stat() const noexcept
        -> const std::vector<stat::Statistics>& {
        return custom_stat_;
    }

    /*!
     * \brief Get the custom outputs without statistics.
     *
     * \return Custom outputs without statistics.
     */
    [[nodiscard]] auto custom_outputs() const noexcept
        -> const std::vector<std::pair<std::string, double>>& {
        return custom_outputs_;
    }

private:
    //! Information of the case.
    BenchmarkFullName case_info_;

    //! Condition.
    BenchmarkCondition cond_;

    //! Name of the measurer.
    std::string measurer_name_;

    //! Number of iterations.
    std::size_t iterations_;

    //! Number of samples.
    std::size_t samples_;

    //! Measured durations.
    std::vector<std::vector<clock::Duration>> durations_;

    //! Statistics of durations.
    stat::Statistics durations_stat_;

    //! Custom outputs with statistics.
    std::vector<std::shared_ptr<stat::CustomStatOutput>> custom_stat_outputs_;

    //! Statistics of custom outputs.
    std::vector<stat::Statistics> custom_stat_;

    //! Custom outputs without statistics.
    std::vector<std::pair<std::string, double>> custom_outputs_;
};

}  // namespace measurer
}  // namespace stat_bench
