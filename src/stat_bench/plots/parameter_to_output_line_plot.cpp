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

#include <iterator>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/line.h>
#include <plotly_plotter/figure_builders/scatter.h>
#include <plotly_plotter/write_html.h>

#include "common_labels.h"
#include "create_data_table.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/util/escape_for_file_name.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

ParameterToOutputLinePlot::ParameterToOutputLinePlot(
    param::ParameterName parameter_name, CustomOutputName custom_output_name,
    PlotOptions options)
    : parameter_name_(std::move(parameter_name)),
      custom_output_name_(std::move(custom_output_name)),
      options_(options),
      name_for_file_(create_name_for_file(
          parameter_name_, custom_output_name_, options_)) {}

auto ParameterToOutputLinePlot::name_for_file() const
    -> const util::Utf8String& {
    return name_for_file_;
}

void ParameterToOutputLinePlot::write(
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)measurer_name;
    (void)group_name;

    const auto& title = custom_output_name_.str();

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

    const auto [data_table, has_error] = create_data_table_with_custom_output(
        measurements, parameter_names, custom_output_name_);
    auto figure_builder = plotly_plotter::figure_builders::line(data_table)
                              .x(parameter_name_.str().str())
                              .y(custom_output_name_.str().str())
                              .group(case_name_label)
                              .log_x(options_.log_parameter())
                              .log_y(options_.log_output());
    if (has_error) {
        figure_builder.error_y(fmt::format("Error of {}", custom_output_name_));
    }
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

auto ParameterToOutputLinePlot::create_name_for_file(
    const param::ParameterName& parameter_name,
    const CustomOutputName& custom_output_name, const PlotOptions& options)
    -> util::Utf8String {
    fmt::memory_buffer buffer;
    fmt::format_to(std::back_inserter(buffer), "{}_by_{}",
        util::escape_for_file_name(custom_output_name.str()),
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
