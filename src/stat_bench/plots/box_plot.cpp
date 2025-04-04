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
 * \brief Implementation of BoxPlot class.
 */
#include "stat_bench/plots/box_plot.h"

#include <memory>
#include <vector>

#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/plots/plot_utils.h"
#include "stat_bench/stat/statistics.h"

namespace stat_bench {
namespace plots {

auto BoxPlot::name_for_file() const -> const util::Utf8String& {
    return name_for_file_;
}

void BoxPlot::write(IPlotter* plotter,
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto& title = measurer_name.str();
    auto figure = plotter->create_figure(title);

    for (const auto& measurement : measurements) {
        const auto& y = measurement.durations_stat().unsorted_samples();

        figure->add_box_trace()->y(y)->name(generate_plot_name(
            measurement.case_info().case_name(), measurement.cond().params()));
    }

    figure->set_y_title(util::Utf8String("Time [sec]"));
    figure->set_log_y();

    figure->write_to_file(file_path);
}

}  // namespace plots
}  // namespace stat_bench
