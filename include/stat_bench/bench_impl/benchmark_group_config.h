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
#include <utility>
#include <vector>

#include "stat_bench/measurement_config.h"
#include "stat_bench/measurer/generate_default_measurement_configs.h"
#include "stat_bench/measurer/measurement_type.h"
#include "stat_bench/plots/i_plot.h"
#include "stat_bench/util/ordered_map.h"

namespace stat_bench::bench_impl {

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
     * \brief Add a measurement configuration to the group.
     *
     * \param[in] config Measurement configuration.
     */
    void add_measurement_config(const MeasurementConfig& config);

    /*!
     * \brief Clear all measurement configurations in the group.
     */
    void clear_measurement_configs() noexcept { measurement_configs_.clear(); }

    /*!
     * \brief Get the plots in the group.
     *
     * \return Plots.
     */
    [[nodiscard]] auto plots() const noexcept
        -> const std::vector<std::shared_ptr<plots::IPlot>>& {
        return plots_;
    }

    /*!
     * \brief Get the measurement configurations in the group.
     *
     * \return Measurement configurations.
     */
    [[nodiscard]] auto measurement_configs() const noexcept -> const
        util::OrderedMap<measurer::MeasurementType, MeasurementConfig>& {
        return measurement_configs_;
    }

private:
    //! Plots only in the group.
    std::vector<std::shared_ptr<plots::IPlot>> plots_;

    //! Configurations of measurements in the group.
    util::OrderedMap<measurer::MeasurementType, MeasurementConfig>
        measurement_configs_{measurer::generate_default_measurement_configs()};
};

}  // namespace stat_bench::bench_impl
