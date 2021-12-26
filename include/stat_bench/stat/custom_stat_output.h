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

#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/stat/statistics.h"

namespace stat_bench {
namespace stat {

/*!
 * \brief Class of custom outputs with statistics.
 */
class CustomStatOutput {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] threads Number of threads.
     * \param[in] samples Number of samples.
     * \param[in] iterations Number of iterations.
     */
    CustomStatOutput(
        std::size_t threads, std::size_t samples, std::size_t iterations)
        : threads_(threads), samples_(samples), iterations_(iterations) {
        data_.reserve(threads_);
        for (std::size_t i = 0; i < threads_; ++i) {
            data_.emplace_back(samples_, 0.0);
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
        data_.at(thread_index).at(sample_index) += val;
    }

    /*!
     * \brief Calculate statistics.
     *
     * \return Statistics.
     */
    [[nodiscard]] auto stat() const -> Statistics {
        Statistics res;
        res.reserve(threads_ * samples_);
        const double inv_iterations = 1.0 / static_cast<double>(iterations_);
        for (const auto& data_per_thread : data_) {
            for (double val : data_per_thread) {
                res.add(val * inv_iterations);
            }
        }
        res.calc();
        return res;
    }

private:
    //! Data.
    std::vector<std::vector<double>> data_{};

    //! Number of threads.
    std::size_t threads_;

    //! Number of samples.
    std::size_t samples_;

    //! Number of iterations.
    std::size_t iterations_;
};

}  // namespace stat
}  // namespace stat_bench
