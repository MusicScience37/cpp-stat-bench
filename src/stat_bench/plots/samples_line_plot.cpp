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
 * \brief Implementation of SamplesLinePlot class.
 */
#include "stat_bench/plots/samples_line_plot.h"

#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/figure_builders/line.h>
#include <plotly_plotter/figure_builders/scatter.h>
#include <plotly_plotter/write_html.h>

#include "common_labels.h"
#include "create_data_table.h"
#include "stat_bench/measurer/measurement_type.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench::plots {

auto SamplesLinePlot::name_for_file() const -> const util::Utf8String& {
    return name_for_file_;
}

void SamplesLinePlot::write(const measurer::MeasurementType& measurement_type,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto& title = measurement_type.str();

    const auto data_table = create_data_table_with_all_time(measurements, {});
    auto figure = plotly_plotter::figure_builders::line(data_table)
                      .x(sample_index_label)
                      .y(time_label)
                      .group(case_name_label)
                      .log_y(true)
                      .create();
    figure.title(title.str());
    plotly_plotter::write_html(file_path, figure);
}

}  // namespace stat_bench::plots
