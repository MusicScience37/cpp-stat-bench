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
 * \brief Declaration of create_data_table function.
 */
#pragma once

#include <utility>
#include <vector>

#include <plotly_plotter/data_table.h>

#include "stat_bench/custom_output_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/param/parameter_name.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Create a data table with the mean of processing time.
 *
 * \param[in] measurements Measurements.
 * \param[in] parameter_names Names of parameters to include in the table.
 * \return Created data table.
 */
[[nodiscard]] auto create_data_table_with_mean_time(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names)
    -> plotly_plotter::data_table;

/*!
 * \brief Create a data table with a custom output.
 *
 * \param[in] measurements Measurements.
 * \param[in] parameter_names Names of parameters to include in the table.
 * \param[in] output_name Name of the custom output to include in the table.
 * \return Created data table and whether custom output has errors.
 */
[[nodiscard]] auto create_data_table_with_custom_output(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names,
    const CustomOutputName& output_name)
    -> std::pair<plotly_plotter::data_table, bool>;

/*!
 * \brief Create a data table with all samples of processing time.
 *
 * \param[in] measurements Measurements.
 * \param[in] parameter_names Names of parameters to include in the table.
 * \return Created data table.
 */
[[nodiscard]] auto create_data_table_with_all_time(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names)
    -> plotly_plotter::data_table;

/*!
 * \brief Create a data table for cumulative distribution functions.
 *
 * \param[in] measurements Measurements.
 * \return Created data table.
 */
[[nodiscard]] auto create_data_table_for_cdf_plot(
    const std::vector<measurer::Measurement>& measurements)
    -> plotly_plotter::data_table;

}  // namespace plots
}  // namespace stat_bench
