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
 * \brief Implementation of ParameterToOutputLinePlot class.
 */
#include "stat_bench/plots/parameter_to_output_line_plot.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "plot_by_parameter_impl.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/escape_for_file_name.h"

namespace stat_bench {
namespace plots {

ParameterToOutputLinePlot::ParameterToOutputLinePlot(
    param::ParameterName parameter_name, CustomOutputName custom_output_name,
    bool plot_parameter_as_log_scale, bool plot_custom_output_as_log_scale)
    : parameter_name_(std::move(parameter_name)),
      custom_output_name_(std::move(custom_output_name)),
      plot_parameter_as_log_scale_(plot_parameter_as_log_scale),
      plot_custom_output_as_log_scale_(plot_custom_output_as_log_scale),
      name_for_file_(fmt::format("{}_by_{}",
          util::escape_for_file_name(custom_output_name_.str()),
          util::escape_for_file_name(parameter_name_.str()))) {}

auto ParameterToOutputLinePlot::name_for_file() const
    -> const util::Utf8String& {
    return name_for_file_;
}

void ParameterToOutputLinePlot::write(IPlotter* plotter,
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto& title = custom_output_name_.str();
    auto figure = plotter->create_figure(title);

    const auto& first_custom_outputs = measurements.front().custom_outputs();
    const auto first_custom_output_iter = std::find_if(
        first_custom_outputs.begin(), first_custom_outputs.end(),
        [this](const auto& pair) { return pair.first == custom_output_name_; });
    if (first_custom_output_iter != first_custom_outputs.end()) {
        // Case of custom output without statistics.
        plot_by_parameter_impl(measurements, parameter_name_, figure.get(),
            [this](const measurer::Measurement& measurement) {
                const auto& custom_outputs = measurement.custom_outputs();
                const auto iter = std::find_if(custom_outputs.begin(),
                    custom_outputs.end(), [this](const auto& pair) {
                        return pair.first == custom_output_name_;
                    });
                if (iter == custom_outputs.end()) {
                    throw StatBenchException(fmt::format(
                        "Custom output {} not found in a measurement.",
                        custom_output_name_));
                }

                return std::make_tuple(
                    measurement.cond().params().get_as_variant(parameter_name_),
                    iter->second);
            });
    } else {
        // Case of custom output with statistics.
        plot_by_parameter_with_y_error_impl(measurements, parameter_name_,
            figure.get(), [this](const measurer::Measurement& measurement) {
                const auto& custom_outputs = measurement.custom_stat_outputs();
                const auto iter = std::find_if(custom_outputs.begin(),
                    custom_outputs.end(), [this](const auto& output) {
                        return output->name() == custom_output_name_;
                    });
                if (iter == custom_outputs.end()) {
                    throw StatBenchException(fmt::format(
                        "Custom output {} not found in a measurement.",
                        custom_output_name_));
                }

                const std::size_t index = iter - custom_outputs.begin();
                const auto& stat = measurement.custom_stat().at(index);
                return std::make_tuple(
                    measurement.cond().params().get_as_variant(parameter_name_),
                    stat.mean(), stat.standard_error());
            });
    }

    figure->set_x_title(parameter_name_.str());
    figure->set_y_title(custom_output_name_.str());
    if (plot_parameter_as_log_scale_) {
        figure->set_log_x();
    }
    if (plot_custom_output_as_log_scale_) {
        figure->set_log_y();
    }

    figure->write_to_file(file_path);
}

}  // namespace plots
}  // namespace stat_bench
