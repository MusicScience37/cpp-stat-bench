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
 * \brief Definition of Statistics class.
 */
#pragma once

// IWYU pragma: no_include  <stddef.h>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

namespace stat_bench {
namespace stat {

/*!
 * \brief Class to calculate statistics.
 */
class Statistics {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] unsorted_samples Unsorted samples.
     * \param[in] sorted_samples Sorted samples.
     * \param[in] mean Mean.
     * \param[in] max Max.
     * \param[in] min Min.
     * \param[in] median Median.
     * \param[in] variance Variance.
     * \param[in] standard_deviation Standard deviation.
     */
    Statistics(std::vector<double> unsorted_samples,
        std::vector<double> sorted_samples, double mean, double max, double min,
        double median, double variance, double standard_deviation)
        : unsorted_samples_(std::move(unsorted_samples)),
          sorted_samples_(std::move(sorted_samples)),
          mean_(mean),
          max_(max),
          min_(min),
          median_(median),
          variance_(variance),
          standard_deviation_(standard_deviation) {}
    /*!
     * \brief Get the unsorted samples.
     *
     * \return Unsorted samples.
     */
    [[nodiscard]] auto unsorted_samples() const noexcept
        -> const std::vector<double>& {
        return unsorted_samples_;
    }

    /*!
     * \brief Get the sorted samples.
     *
     * \return Sorted samples.
     */
    [[nodiscard]] auto sorted_samples() const noexcept
        -> const std::vector<double>& {
        return sorted_samples_;
    }

    /*!
     * \brief Get the mean.
     *
     * \return Mean.
     */
    [[nodiscard]] auto mean() const noexcept -> double { return mean_; }

    /*!
     * \brief Get the max.
     *
     * \return Max.
     */
    [[nodiscard]] auto max() const noexcept -> double { return max_; }

    /*!
     * \brief Get the min.
     *
     * \return Min.
     */
    [[nodiscard]] auto min() const noexcept -> double { return min_; }

    /*!
     * \brief Get the variance.
     *
     * \return Variance.
     */
    [[nodiscard]] auto variance() const noexcept -> double { return variance_; }

    /*!
     * \brief Get the standard deviation.
     *
     * \return Standard deviation.
     */
    [[nodiscard]] auto standard_deviation() const noexcept -> double {
        return standard_deviation_;
    }

private:
    //! Unsorted samples.
    std::vector<double> unsorted_samples_{};

    //! Sorted samples.
    std::vector<double> sorted_samples_{};

    //! Mean.
    double mean_{0.0};

    //! Max.
    double max_{std::numeric_limits<double>::min()};

    //! Min.
    double min_{std::numeric_limits<double>::max()};

    //! Median.
    double median_{0.0};

    //! Variance.
    double variance_{0.0};

    //! Standard deviation.
    double standard_deviation_{0.0};
};

}  // namespace stat
}  // namespace stat_bench
