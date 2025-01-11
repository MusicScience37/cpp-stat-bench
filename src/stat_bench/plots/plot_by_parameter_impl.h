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
 * \brief Definition of plot_by_parameter_impl function.
 */
#pragma once

// IWYU pragma: no_include <string>

#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include <fmt/format.h>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/plots/plot_utils.h"
#include "stat_bench/util/ordered_map.h"
#include "stat_bench/util/utf8_string.h"

namespace std {

/*!
 * \brief Implementation of std::hash for
 * std::pair<stat_bench::BenchmarkCaseName, stat_bench::param::ParameterDict>.
 */
template <>
class hash<std::pair<stat_bench::BenchmarkCaseName,
    stat_bench::param::ParameterDict>> {
public:
    /*!
     * \brief Operator to calculate hash value.
     *
     * \param[in] value Value to calculate hash value.
     * \return Hash value.
     */
    auto operator()(const std::pair<stat_bench::BenchmarkCaseName,
        stat_bench::param::ParameterDict>& value) const -> size_t {
        return std::hash<stat_bench::BenchmarkCaseName>{}(value.first) ^
            std::hash<stat_bench::param::ParameterDict>{}(value.second);
    }
};

}  // namespace std

namespace stat_bench {
namespace plots {

/*!
 * \brief Plot data by parameter.
 *
 * \tparam MeasurementToPlotDataFunction Type of the function to get data from a
 * measurement.
 * \param[in] measurements Measurements.
 * \param[in] parameter_name Parameter name.
 * \param[in,out] figure Figure to plot.
 * \param[in] convert_measurement_to_plot_data Function to get data from a
 * measurement.
 */
template <typename MeasurementToPlotDataFunction>
void plot_by_parameter_impl(
    const std::vector<measurer::Measurement>& measurements,
    const param::ParameterName& parameter_name, IFigure* figure,
    MeasurementToPlotDataFunction&& convert_measurement_to_plot_data) {
    struct FigureData {
        std::vector<param::ParameterValueVariant> x;
        std::vector<double> y;
    };
    util::OrderedMap<std::pair<BenchmarkCaseName, param::ParameterDict>,
        FigureData>
        figure_data_map;
    for (const auto& measurement : measurements) {
        const auto& case_name = measurement.case_info().case_name();
        const auto& params = measurement.cond().params();
        const auto params_without_target = params.clone_without(parameter_name);
        const auto key = std::make_pair(case_name, params_without_target);
        auto& figure_data = figure_data_map[key];

        const auto [x, y] = convert_measurement_to_plot_data(measurement);

        figure_data.x.push_back(x);
        figure_data.y.push_back(y);
    }

    for (const auto& [key, figure_data] : figure_data_map) {
        figure->add_line_trace()
            ->x(figure_data.x)
            ->y(figure_data.y)
            ->name(generate_plot_name(key.first, key.second));
    }
}

/*!
 * \brief Plot data by parameter with error in x.
 *
 * \tparam MeasurementToPlotDataFunction Type of the function to get data from a
 * measurement.
 * \param[in] measurements Measurements.
 * \param[in] parameter_name Parameter name.
 * \param[in,out] figure Figure to plot.
 * \param[in] convert_measurement_to_plot_data Function to get data from a
 * measurement.
 */
template <typename MeasurementToPlotDataFunction>
void plot_by_parameter_with_x_error_with_param_impl(
    const std::vector<measurer::Measurement>& measurements,
    const param::ParameterName& parameter_name, IFigure* figure,
    MeasurementToPlotDataFunction&& convert_measurement_to_plot_data) {
    struct FigureData {
        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> x_error;
        std::vector<util::Utf8String> texts;
    };
    util::OrderedMap<std::pair<BenchmarkCaseName, param::ParameterDict>,
        FigureData>
        figure_data_map;
    for (const auto& measurement : measurements) {
        const auto& case_name = measurement.case_info().case_name();
        const auto& params = measurement.cond().params();
        const auto params_without_target = params.clone_without(parameter_name);
        const auto key = std::make_pair(case_name, params_without_target);
        auto& figure_data = figure_data_map[key];

        const auto [x, y, x_error] =
            convert_measurement_to_plot_data(measurement);

        figure_data.x.push_back(x);
        figure_data.y.push_back(y);
        figure_data.x_error.push_back(x_error);
        std::visit(
            [&figure_data, &parameter_name](const auto& value) {
                figure_data.texts.push_back(util::Utf8String(
                    fmt::format("{}={}", parameter_name, value)));
            },
            measurement.cond().params().get_as_variant(parameter_name));
    }

    for (const auto& [key, figure_data] : figure_data_map) {
        figure->add_line_trace()
            ->x(figure_data.x)
            ->y(figure_data.y)
            ->x_error(figure_data.x_error)
            ->text(figure_data.texts)
            ->name(generate_plot_name(key.first, key.second));
    }
}

/*!
 * \brief Plot data by parameter with error in y.
 *
 * \tparam MeasurementToPlotDataFunction Type of the function to get data from a
 * measurement.
 * \param[in] measurements Measurements.
 * \param[in] parameter_name Parameter name.
 * \param[in,out] figure Figure to plot.
 * \param[in] convert_measurement_to_plot_data Function to get data from a
 * measurement.
 */
template <typename MeasurementToPlotDataFunction>
void plot_by_parameter_with_y_error_impl(
    const std::vector<measurer::Measurement>& measurements,
    const param::ParameterName& parameter_name, IFigure* figure,
    MeasurementToPlotDataFunction&& convert_measurement_to_plot_data) {
    struct FigureData {
        std::vector<param::ParameterValueVariant> x;
        std::vector<double> y;
        std::vector<double> y_error;
    };
    util::OrderedMap<std::pair<BenchmarkCaseName, param::ParameterDict>,
        FigureData>
        figure_data_map;
    for (const auto& measurement : measurements) {
        const auto& case_name = measurement.case_info().case_name();
        const auto& params = measurement.cond().params();
        const auto params_without_target = params.clone_without(parameter_name);
        const auto key = std::make_pair(case_name, params_without_target);
        auto& figure_data = figure_data_map[key];

        const auto [x, y, y_error] =
            convert_measurement_to_plot_data(measurement);

        figure_data.x.push_back(x);
        figure_data.y.push_back(y);
        figure_data.y_error.push_back(y_error);
    }

    for (const auto& [key, figure_data] : figure_data_map) {
        figure->add_line_trace()
            ->x(figure_data.x)
            ->y(figure_data.y)
            ->y_error(figure_data.y_error)
            ->name(generate_plot_name(key.first, key.second));
    }
}

/*!
 * \brief Plot data by parameter with error in x and y.
 *
 * \tparam MeasurementToPlotDataFunction Type of the function to get data from a
 * measurement.
 * \param[in] measurements Measurements.
 * \param[in] parameter_name Parameter name.
 * \param[in,out] figure Figure to plot.
 * \param[in] convert_measurement_to_plot_data Function to get data from a
 * measurement.
 */
template <typename MeasurementToPlotDataFunction>
void plot_by_parameter_with_xy_error_with_param_impl(
    const std::vector<measurer::Measurement>& measurements,
    const param::ParameterName& parameter_name, IFigure* figure,
    MeasurementToPlotDataFunction&& convert_measurement_to_plot_data) {
    struct FigureData {
        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> x_error;
        std::vector<double> y_error;
        std::vector<util::Utf8String> texts;
    };
    util::OrderedMap<std::pair<BenchmarkCaseName, param::ParameterDict>,
        FigureData>
        figure_data_map;
    for (const auto& measurement : measurements) {
        const auto& case_name = measurement.case_info().case_name();
        const auto& params = measurement.cond().params();
        const auto params_without_target = params.clone_without(parameter_name);
        const auto key = std::make_pair(case_name, params_without_target);
        auto& figure_data = figure_data_map[key];

        const auto [x, y, x_error, y_error] =
            convert_measurement_to_plot_data(measurement);

        figure_data.x.push_back(x);
        figure_data.y.push_back(y);
        figure_data.x_error.push_back(x_error);
        figure_data.y_error.push_back(y_error);
        std::visit(
            [&figure_data, &parameter_name](const auto& value) {
                figure_data.texts.push_back(util::Utf8String(
                    fmt::format("{}={}", parameter_name, value)));
            },
            measurement.cond().params().get_as_variant(parameter_name));
    }

    for (const auto& [key, figure_data] : figure_data_map) {
        figure->add_line_trace()
            ->x(figure_data.x)
            ->y(figure_data.y)
            ->x_error(figure_data.x_error)
            ->y_error(figure_data.y_error)
            ->text(figure_data.texts)
            ->name(generate_plot_name(key.first, key.second));
    }
}

}  // namespace plots
}  // namespace stat_bench
