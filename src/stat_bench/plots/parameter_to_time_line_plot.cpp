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

#include <memory>
#include <tuple>
#include <utility>

#include <fmt/format.h>

#include "plot_by_parameter_impl.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/stat/statistics.h"
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

void ParameterToTimeLinePlot::write(IPlotter* plotter,
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto& title = measurer_name.str();
    auto figure = plotter->create_figure(title);
    plot_by_parameter_with_y_error_impl(measurements, parameter_name_,
        figure.get(), [this](const measurer::Measurement& measurement) {
            return std::make_tuple(
                measurement.cond().params().get_as_variant(parameter_name_),
                measurement.durations_stat().mean(),
                measurement.durations_stat().standard_error());
        });

    figure->set_x_title(parameter_name_.str());
    figure->set_y_title(util::Utf8String("Time [sec]"));
    if (plot_parameter_as_log_scale_) {
        figure->set_log_x();
    }
    figure->set_log_y();

    figure->write_to_file(file_path);
}

}  // namespace plots
}  // namespace stat_bench
