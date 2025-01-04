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

#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/plots/plot_utils.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/util/escape_for_file_name.h"
#include "stat_bench/util/ordered_map.h"

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

    struct FigureData {
        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> y_error;
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

        figure_data.x.push_back(params.get_as_double(parameter_name_));
        figure_data.y.push_back(measurement.durations_stat().mean());
        figure_data.y_error.push_back(
            measurement.durations_stat().standard_error());
    }

    const auto& title = measurer_name.str();
    auto figure = plotter->create_figure(title);
    for (const auto& [key, figure_data] : figure_data_map) {
        figure->add_line_with_error(figure_data.x, figure_data.y,
            figure_data.y_error, generate_plot_name(key.first, key.second));
    }

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
