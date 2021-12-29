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
 * \brief Definition of CustomStatOutput class.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace stat {

/*!
 * \brief Enumeration of types of analysis applied to custom outputs.
 */
enum CustomOutputAnalysisType {
    mean,         //!< Mean per sample.
    rate_per_sec  //!< Rate per sec.
};

/*!
 * \brief Class of custom outputs with statistics.
 */
class CustomStatOutput {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] name Name.
     * \param[in] threads Number of threads.
     * \param[in] samples Number of samples (including warming_up_samples).
     * \param[in] warming_up_samples Number of samples for warming up. (They're
     * ignored.)
     * \param[in] iterations Number of iterations. \param[in]
     * analysis_type Type of analysis.
     */
    CustomStatOutput(std::string name, std::size_t threads, std::size_t samples,
        std::size_t warming_up_samples, std::size_t iterations,
        CustomOutputAnalysisType analysis_type)
        : name_(std::move(name)),
          threads_(threads),
          samples_(samples),
          warming_up_samples_(warming_up_samples),
          iterations_(iterations),
          analysis_type_(analysis_type) {
        if (samples <= warming_up_samples) {
            throw StatBenchException("Invalid number of samples.");
        }
        data_.reserve(threads_);
        const std::size_t used_samples = samples - warming_up_samples;
        for (std::size_t i = 0; i < threads_; ++i) {
            data_.emplace_back(used_samples, 0.0);
        }
    }

    /*!
     * \brief Add a value.
     *
     * \param[in] thread_index Index of the thread.
     * \param[in] sample_index Index of the sample.
     * \param[in] val Value of the current iteration.
     */
    void add(std::size_t thread_index, std::size_t sample_index, double val) {
        if (sample_index < warming_up_samples_) {
            return;
        }
        data_.at(thread_index).at(sample_index - warming_up_samples_) += val;
    }

    /*!
     * \brief Preprocess data.
     *
     * \param[in] durations Durations.
     */
    void preprocess(
        const std::vector<std::vector<clock::Duration>>& durations) {
        const std::size_t used_samples = samples_ - warming_up_samples_;
        for (std::size_t i = 0; i < threads_; ++i) {
            for (std::size_t j = 0; j < used_samples; ++j) {
                double& val = data_.at(i).at(j);

                switch (analysis_type_) {
                case CustomOutputAnalysisType::mean:
                    val /= static_cast<double>(iterations_);
                    break;
                case CustomOutputAnalysisType::rate_per_sec:
                    val /= durations.at(i).at(j).seconds();
                    break;
                }
            }
        }
    }

    /*!
     * \brief Calculate statistics.
     *
     * \return Statistics.
     */
    [[nodiscard]] auto stat() const -> Statistics {
        const std::size_t used_samples = samples_ - warming_up_samples_;
        Statistics res;
        res.reserve(threads_ * used_samples);
        for (std::size_t i = 0; i < threads_; ++i) {
            for (std::size_t j = 0; j < used_samples; ++j) {
                const double val = data_.at(i).at(j);
                res.add(val);
            }
        }
        res.calc();
        return res;
    }

    /*!
     * \brief Get the name.
     *
     * \return Name.
     */
    [[nodiscard]] auto name() const noexcept -> const std::string& {
        return name_;
    }

    /*!
     * \brief Get data.
     *
     * \return Data.
     */
    [[nodiscard]] auto data() const noexcept
        -> const std::vector<std::vector<double>>& {
        return data_;
    }

private:
    //! Name.
    std::string name_;

    //! Data.
    std::vector<std::vector<double>> data_{};

    //! Number of threads.
    std::size_t threads_;

    //! Number of total samples.
    std::size_t samples_;

    //! Number of samples for warming up.
    std::size_t warming_up_samples_;

    //! Number of iterations.
    std::size_t iterations_;

    //! Type of analysis.
    CustomOutputAnalysisType analysis_type_;
};

}  // namespace stat
}  // namespace stat_bench
