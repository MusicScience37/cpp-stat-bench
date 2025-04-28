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
 * \brief Implementation of TimeToOutputByParameterLinePlot class.
 */
#include "stat_bench/plots/time_to_output_by_parameter_line_plot.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <plotly_plotter/figure_builders/line.h>
#include <plotly_plotter/write_html.h>

#include "common_labels.h"
#include "create_data_table.h"
#include "plot_by_parameter_impl.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/escape_for_file_name.h"

namespace stat_bench {
namespace plots {

TimeToOutputByParameterLinePlot::TimeToOutputByParameterLinePlot(
    param::ParameterName parameter_name, CustomOutputName custom_output_name,
    bool plot_custom_output_as_log_scale)
    : parameter_name_(std::move(parameter_name)),
      custom_output_name_(std::move(custom_output_name)),
      plot_custom_output_as_log_scale_(plot_custom_output_as_log_scale),
      name_for_file_(fmt::format("to_{}_by_{}",
          util::escape_for_file_name(custom_output_name_.str()),
          util::escape_for_file_name(parameter_name_.str()))) {}

auto TimeToOutputByParameterLinePlot::name_for_file() const
    -> const util::Utf8String& {
    return name_for_file_;
}

void TimeToOutputByParameterLinePlot::write(IPlotter* plotter,
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)plotter;
    (void)measurer_name;
    (void)group_name;

    const auto& title = custom_output_name_.str();

    const auto [data_table, has_error] = create_data_table_with_custom_output(
        measurements, {parameter_name_}, custom_output_name_);
    auto figure_builder = plotly_plotter::figure_builders::line(data_table)
                              .x(time_label)
                              .error_x(time_error_label)
                              .y(custom_output_name_.str().str())
                              .group(case_name_label)
                              .log_x(true)
                              .log_y(plot_custom_output_as_log_scale_)
                              .hover_data({parameter_name_.str().str()});
    if (has_error) {
        figure_builder.error_y(fmt::format("Error of {}", custom_output_name_));
    }
    auto figure = figure_builder.create();
    figure.title(title.str());
    plotly_plotter::write_html(file_path, figure);
}

}  // namespace plots
}  // namespace stat_bench
