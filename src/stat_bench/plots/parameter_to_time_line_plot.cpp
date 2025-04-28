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
 * \brief Implementation of ParameterToTimeLinePlot class.
 */
#include "stat_bench/plots/parameter_to_time_line_plot.h"

#include <utility>
#include <vector>

#include <fmt/format.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/line.h>
#include <plotly_plotter/figure_builders/scatter.h>
#include <plotly_plotter/write_html.h>

#include "common_labels.h"
#include "create_data_table.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/util/escape_for_file_name.h"

namespace stat_bench {
namespace plots {

ParameterToTimeLinePlot::ParameterToTimeLinePlot(
    param::ParameterName parameter_name, bool plot_parameter_as_log_scale)
    : parameter_name_(std::move(parameter_name)),
      plot_parameter_as_log_scale_(plot_parameter_as_log_scale),
      name_for_file_(fmt::format(
          "by_{}", util::escape_for_file_name(parameter_name_.str()))) {}

auto ParameterToTimeLinePlot::name_for_file() const -> const util::Utf8String& {
    return name_for_file_;
}

void ParameterToTimeLinePlot::write(const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto& title = measurer_name.str();

    const auto data_table =
        create_data_table_with_mean_time(measurements, {parameter_name_});
    auto figure = plotly_plotter::figure_builders::line(data_table)
                      .x(parameter_name_.str().str())
                      .y(time_label)
                      .error_y(time_error_label)
                      .group(case_name_label)
                      .log_x(plot_parameter_as_log_scale_)
                      .log_y(true)
                      .create();
    figure.title(title.str());
    plotly_plotter::write_html(file_path, figure);
}

}  // namespace plots
}  // namespace stat_bench
