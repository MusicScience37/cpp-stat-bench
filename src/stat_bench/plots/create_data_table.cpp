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

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include <fmt/base.h>
#include <fmt/format.h>
#include <plotly_plotter/json_converter_decl.h>
#include <plotly_plotter/json_value.h>

#include "common_labels.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/plots/plot_utils.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/utf8_string.h"

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

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for
 * stat_bench::param::ParameterValueVariant.
 */
template <>
struct formatter<stat_bench::param::ParameterValueVariant>
    : public formatter<string_view> {
    /*!
     * \brief Format.
     *
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    auto format(const stat_bench::param::ParameterValueVariant& val,
        format_context& context) const -> format_context::iterator {
        return std::visit(
            [&context](const auto& value) {
                return fmt::format_to(context.out(), "{}", value);
            },
            val);
    }
};

}  // namespace fmt

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

namespace {

auto create_data_table_with_custom_output_without_stat(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names,
    const CustomOutputName& output_name)
    -> std::pair<plotly_plotter::data_table, bool> {
    std::vector<std::string> case_names;
    std::vector<double> processing_times;
    std::vector<double> processing_time_errors;
    std::unordered_map<param::ParameterName,
        std::vector<param::ParameterValueVariant>>
        parameter_values_map;
    std::vector<double> custom_outputs;

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

        const auto& current_custom_outputs = measurement.custom_outputs();
        const auto iter = std::find_if(current_custom_outputs.begin(),
            current_custom_outputs.end(), [&output_name](const auto& pair) {
                return pair.first == output_name;
            });
        if (iter == current_custom_outputs.end()) {
            throw StatBenchException(fmt::format(
                "Custom output {} not found in a measurement.", output_name));
        }
        custom_outputs.push_back(iter->second);
    }

    plotly_plotter::data_table table;
    table.emplace(case_name_label, std::move(case_names));
    table.emplace(time_label, std::move(processing_times));
    table.emplace(time_error_label, std::move(processing_time_errors));
    for (const auto& parameter_name : parameter_names) {
        table.emplace(parameter_name.str().str(),
            std::move(parameter_values_map[parameter_name]));
    }
    table.emplace(output_name.str().str(), std::move(custom_outputs));

    constexpr bool has_error = false;
    return {std::move(table), has_error};
}

auto create_data_table_with_custom_output_with_stat(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names,
    const CustomOutputName& output_name)
    -> std::pair<plotly_plotter::data_table, bool> {
    std::vector<std::string> case_names;
    std::vector<double> processing_times;
    std::vector<double> processing_time_errors;
    std::unordered_map<param::ParameterName,
        std::vector<param::ParameterValueVariant>>
        parameter_values_map;
    std::vector<double> custom_outputs;
    std::vector<double> custom_output_errors;

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

        const auto& current_custom_outputs = measurement.custom_stat_outputs();
        const auto iter = std::find_if(current_custom_outputs.begin(),
            current_custom_outputs.end(), [&output_name](const auto& output) {
                return output->name() == output_name;
            });
        if (iter == current_custom_outputs.end()) {
            throw StatBenchException(fmt::format(
                "Custom output {} not found in a measurement.", output_name));
        }
        const std::size_t index = iter - current_custom_outputs.begin();
        const auto& stat = measurement.custom_stat().at(index);
        custom_outputs.push_back(stat.mean());
        custom_output_errors.push_back(stat.standard_error());
    }

    plotly_plotter::data_table table;
    table.emplace(case_name_label, std::move(case_names));
    table.emplace(time_label, std::move(processing_times));
    table.emplace(time_error_label, std::move(processing_time_errors));
    for (const auto& parameter_name : parameter_names) {
        table.emplace(parameter_name.str().str(),
            std::move(parameter_values_map[parameter_name]));
    }
    table.emplace(output_name.str().str(), std::move(custom_outputs));
    table.emplace(fmt::format("Error of {}", output_name.str()),
        std::move(custom_output_errors));

    constexpr bool has_error = true;
    return {std::move(table), has_error};
}

}  // namespace

auto create_data_table_with_custom_output(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names,
    const CustomOutputName& output_name)
    -> std::pair<plotly_plotter::data_table, bool> {
    const auto& first_custom_outputs = measurements.front().custom_outputs();
    const auto first_custom_output_iter = std::find_if(
        first_custom_outputs.begin(), first_custom_outputs.end(),
        [&output_name](const auto& pair) { return pair.first == output_name; });
    if (first_custom_output_iter != first_custom_outputs.end()) {
        // Case of custom output without statistics.
        return create_data_table_with_custom_output_without_stat(
            measurements, parameter_names, output_name);
    }
    // Case of custom output with statistics.
    return create_data_table_with_custom_output_with_stat(
        measurements, parameter_names, output_name);
}

auto create_data_table_with_all_time(
    const std::vector<measurer::Measurement>& measurements,
    const std::vector<param::ParameterName>& parameter_names)
    -> plotly_plotter::data_table {
    std::vector<std::string> case_names;
    std::vector<std::size_t> indices;
    std::vector<double> processing_times;
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

        const auto processing_times_for_plot =
            measurement.durations_stat().unsorted_samples();
        const std::size_t num_samples = processing_times_for_plot.size();

        case_names.insert(
            case_names.end(), num_samples, case_name_for_plot.str());

        for (std::size_t i = 0; i < num_samples; ++i) {
            indices.push_back(i + 1);
        }

        processing_times.insert(processing_times.end(),
            processing_times_for_plot.begin(), processing_times_for_plot.end());

        for (const auto& parameter_name : parameter_names) {
            const auto parameter_value =
                measurement.cond().params().get_as_variant(parameter_name);
            parameter_values_map[parameter_name].insert(
                parameter_values_map[parameter_name].end(), num_samples,
                parameter_value);
        }
    }

    plotly_plotter::data_table table;
    table.emplace(case_name_label, std::move(case_names));
    table.emplace(sample_index_label, std::move(indices));
    table.emplace(time_label, std::move(processing_times));
    for (const auto& parameter_name : parameter_names) {
        table.emplace(parameter_name.str().str(),
            std::move(parameter_values_map[parameter_name]));
    }
    return table;
}

auto create_data_table_for_cdf_plot(
    const std::vector<measurer::Measurement>& measurements)
    -> plotly_plotter::data_table {
    std::vector<std::string> case_names;
    std::vector<double> probabilities;
    std::vector<double> processing_times;

    for (const auto& measurement : measurements) {
        const auto& case_name = measurement.case_info().case_name();
        const auto& params = measurement.cond().params();
        const auto case_name_for_plot = generate_plot_name(case_name, params);

        const auto processing_times_for_plot =
            measurement.durations_stat().sorted_samples();
        const std::size_t num_samples = processing_times_for_plot.size();

        case_names.insert(
            case_names.end(), num_samples, case_name_for_plot.str());
        for (std::size_t i = 0; i < num_samples; ++i) {
            probabilities.push_back(
                static_cast<double>(i + 1) / static_cast<double>(num_samples));
        }
        processing_times.insert(processing_times.end(),
            processing_times_for_plot.begin(), processing_times_for_plot.end());
    }

    plotly_plotter::data_table table;
    table.emplace(case_name_label, std::move(case_names));
    table.emplace(cumulative_probability_label, std::move(probabilities));
    table.emplace(time_label, std::move(processing_times));
    return table;
}

}  // namespace plots
}  // namespace stat_bench
