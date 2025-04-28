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
 * \brief Implementation of create_data_table function.
 */
#include "create_data_table.h"

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include <fmt/std.h>

#include "common_labels.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/plots/plot_utils.h"

namespace plotly_plotter {

/*!
 * \brief Implementation of plotly_plotter::json_converter for
 * stat_bench::param::ParameterValueVariant.
 */
template <>
class json_converter<stat_bench::param::ParameterValueVariant> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(
        const stat_bench::param::ParameterValueVariant& from, json_value& to) {
        std::visit([&to](const auto& value) { to = value; }, from);
    }
};

}  // namespace plotly_plotter

namespace stat_bench {
namespace plots {

auto create_data_table_with_mean_time(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names)
    -> plotly_plotter::data_table {
    std::vector<std::string> case_names;
    std::vector<double> processing_times;
    std::vector<double> processing_time_errors;
    std::unordered_map<param::ParameterName,
        std::vector<param::ParameterValueVariant>>
        parameter_values_map;

    for (const auto& measurement : measurements) {
        const auto& case_name = measurement.case_info().case_name();
        auto params_without_target = measurement.cond().params();
        for (const auto& parameter_name : parameter_names) {
            params_without_target =
                params_without_target.clone_without(parameter_name);
        }
        const auto case_name_for_plot =
            generate_plot_name(case_name, params_without_target);
        case_names.push_back(case_name_for_plot.str());

        processing_times.push_back(measurement.durations_stat().mean());
        processing_time_errors.push_back(
            measurement.durations_stat().standard_error());

        for (const auto& parameter_name : parameter_names) {
            parameter_values_map[parameter_name].push_back(
                measurement.cond().params().get_as_variant(parameter_name));
        }
    }

    plotly_plotter::data_table table;
    table.emplace(case_name_label, std::move(case_names));
    table.emplace(time_label, std::move(processing_times));
    table.emplace(time_error_label, std::move(processing_time_errors));
    for (const auto& parameter_name : parameter_names) {
        table.emplace(parameter_name.str().str(),
            std::move(parameter_values_map[parameter_name]));
    }
    return table;
}

}  // namespace plots
}  // namespace stat_bench
