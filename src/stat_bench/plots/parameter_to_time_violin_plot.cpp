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
 * \brief Implementation of ParameterToTimeViolinPlot class.
 */
#include "stat_bench/plots/parameter_to_time_violin_plot.h"

#include <iterator>
#include <utility>
#include <vector>

#include <fmt/base.h>
#include <fmt/format.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/violin.h>
#include <plotly_plotter/write_html.h>

#include "common_labels.h"
#include "create_data_table.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/util/escape_for_file_name.h"
#include "stat_bench/util/string_view.h"

namespace stat_bench {
namespace plots {

ParameterToTimeViolinPlot::ParameterToTimeViolinPlot(
    param::ParameterName parameter_name, PlotOptions options)
    : parameter_name_(std::move(parameter_name)),
      options_(options),
      name_for_file_(create_name_for_file(parameter_name_, options_)) {}

auto ParameterToTimeViolinPlot::name_for_file() const
    -> const util::Utf8String& {
    return name_for_file_;
}

void ParameterToTimeViolinPlot::write(
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto& title = measurer_name.str();

    std::vector<param::ParameterName> parameter_names;
    parameter_names.push_back(parameter_name_);
    if (!options_.subplot_column_parameter_name().empty()) {
        parameter_names.emplace_back(
            options_.subplot_column_parameter_name().data());
    }
    if (!options_.subplot_row_parameter_name().empty()) {
        parameter_names.emplace_back(
            options_.subplot_row_parameter_name().data());
    }

    const auto data_table =
        create_data_table_with_all_time(measurements, parameter_names);
    auto figure_builder = plotly_plotter::figure_builders::violin(data_table)
                              .x(parameter_name_.str().str())
                              .y(time_label)
                              .group(case_name_label)
                              .log_y(true)
                              .show_box(true)
                              .show_mean_line(true);
    if (!options_.subplot_column_parameter_name().empty()) {
        figure_builder.subplot_column(
            options_.subplot_column_parameter_name().data());
    }
    if (!options_.subplot_row_parameter_name().empty()) {
        figure_builder.subplot_row(
            options_.subplot_row_parameter_name().data());
    }
    auto figure = figure_builder.create();
    figure.title(title.str());
    plotly_plotter::write_html(file_path, figure);
}

auto ParameterToTimeViolinPlot::create_name_for_file(
    const param::ParameterName& parameter_name, const PlotOptions& options)
    -> util::Utf8String {
    fmt::memory_buffer buffer;
    fmt::format_to(std::back_inserter(buffer), "by_{}_violin",
        util::escape_for_file_name(parameter_name.str()));
    if (!options.subplot_column_parameter_name().empty()) {
        fmt::format_to(std::back_inserter(buffer), "_by_{}",
            util::escape_for_file_name(util::Utf8String(
                options.subplot_column_parameter_name().data())));
    }
    if (!options.subplot_row_parameter_name().empty()) {
        fmt::format_to(std::back_inserter(buffer), "_by_{}",
            util::escape_for_file_name(
                util::Utf8String(options.subplot_row_parameter_name().data())));
    }
    return util::Utf8String(std::string(buffer.data(), buffer.size()));
}

}  // namespace plots
}  // namespace stat_bench
