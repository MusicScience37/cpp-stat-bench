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
 * \brief Implementation of ViolinPlot class.
 */
#include "stat_bench/plots/violin_plot.h"

#include <memory>
#include <vector>

#include <plotly_plotter/figure_builders/violin.h>
#include <plotly_plotter/write_html.h>

#include "common_labels.h"
#include "create_data_table.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/plots/plot_utils.h"
#include "stat_bench/stat/statistics.h"

namespace stat_bench {
namespace plots {

auto ViolinPlot::name_for_file() const -> const util::Utf8String& {
    return name_for_file_;
}

void ViolinPlot::write(IPlotter* plotter,
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)plotter;
    (void)group_name;

    const auto& title = measurer_name.str();

    const auto data_table = create_data_table_with_all_time(measurements, {});
    auto figure = plotly_plotter::figure_builders::violin(data_table)
                      .y(time_label)
                      .group(case_name_label)
                      .log_y(true)
                      .show_box(true)
                      .show_mean_line(true)
                      .create();
    figure.title(title.str());
    plotly_plotter::write_html(file_path, figure);
}

}  // namespace plots
}  // namespace stat_bench
