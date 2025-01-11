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

#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include <fmt/format.h>

#include "plot_by_parameter_impl.h"  // IWYU pragma: keep
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/plots/plot_utils.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/util/escape_for_file_name.h"
#include "stat_bench/util/ordered_map.h"

namespace stat_bench {
namespace plots {

ParameterToTimeViolinPlot::ParameterToTimeViolinPlot(
    param::ParameterName parameter_name)
    : parameter_name_(std::move(parameter_name)),
      name_for_file_(fmt::format(
          "by_{}_violin", util::escape_for_file_name(parameter_name_.str()))) {}

auto ParameterToTimeViolinPlot::name_for_file() const
    -> const util::Utf8String& {
    return name_for_file_;
}

void ParameterToTimeViolinPlot::write(IPlotter* plotter,
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto& title = measurer_name.str();
    auto figure = plotter->create_figure(title);

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
        const auto params_without_target =
            params.clone_without(parameter_name_);
        const auto key = std::make_pair(case_name, params_without_target);
        auto& figure_data = figure_data_map[key];

        const param::ParameterValueVariant x_value = std::visit(
            [](const auto& value) { return fmt::format("{}", value); },
            measurement.cond().params().get_as_variant(parameter_name_));
        const auto& y_list = measurement.durations_stat().unsorted_samples();
        const auto x_list =
            std::vector<param::ParameterValueVariant>(y_list.size(), x_value);

        figure_data.x.insert(figure_data.x.end(), x_list.begin(), x_list.end());
        figure_data.y.insert(figure_data.y.end(), y_list.begin(), y_list.end());
    }

    for (const auto& [key, figure_data] : figure_data_map) {
        figure->add_violin_trace()
            ->x(figure_data.x)
            ->y(figure_data.y)
            ->name(generate_plot_name(key.first, key.second));
    }

    figure->set_x_title(parameter_name_.str());
    figure->set_y_title(util::Utf8String("Time [sec]"));
    figure->set_log_y();

    figure->write_to_file(file_path);
}

}  // namespace plots
}  // namespace stat_bench
