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
 * \brief Definition of BenchmarkGroupConfig class.
 */
#pragma once

#include <memory>
#include <vector>

#include "stat_bench/plots/i_plot.h"

namespace stat_bench {
namespace bench_impl {

/*!
 * \brief Class of configuration of a group of cases in benchmarks.
 */
class BenchmarkGroupConfig {
public:
    /*!
     * \brief Constructor.
     */
    BenchmarkGroupConfig() = default;

    /*!
     * \brief Add a plot to the group.
     *
     * \param[in] plot Plot.
     */
    void add_plot(std::shared_ptr<plots::IPlot> plot) {
        plots_.push_back(std::move(plot));
    }

    /*!
     * \brief Get the plots in the group.
     *
     * \return Plots.
     */
    [[nodiscard]] auto plots() const noexcept
        -> const std::vector<std::shared_ptr<plots::IPlot>>& {
        return plots_;
    }

private:
    //! Plots only in the group.
    std::vector<std::shared_ptr<plots::IPlot>> plots_;
};

}  // namespace bench_impl
}  // namespace stat_bench
