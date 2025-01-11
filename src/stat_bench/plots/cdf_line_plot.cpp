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
 * \brief Implementation of CdfLinePlot class.
 */
#include "stat_bench/plots/cdf_line_plot.h"

#include <cstddef>
#include <memory>
#include <vector>

#include <fmt/format.h>

#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/plots/plot_utils.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

auto CdfLinePlot::name_for_file() const -> const util::Utf8String& {
    return name_for_file_;
}

void CdfLinePlot::write(IPlotter* plotter,
    const measurer::MeasurerName& measurer_name,
    const BenchmarkGroupName& group_name,
    const std::vector<measurer::Measurement>& measurements,
    const std::string& file_path) {
    (void)group_name;

    const auto title = util::Utf8String(fmt::format(
        "Cumulative Distribution Function of {}", measurer_name.str()));
    auto figure = plotter->create_figure(title);

    for (const auto& measurement : measurements) {
        const std::vector<double>& x =
            measurement.durations_stat().sorted_samples();

        const std::size_t samples = x.size();
        std::vector<double> y;
        y.reserve(samples);
        for (std::size_t i = 0; i < samples; ++i) {
            y.push_back(
                static_cast<double>(i + 1) / static_cast<double>(samples));
        }

        figure->add_line_trace()->x(x)->y(y)->name(generate_plot_name(
            measurement.case_info().case_name(), measurement.cond().params()));
    }

    figure->set_x_title(util::Utf8String("Time [sec]"));
    figure->set_y_title(util::Utf8String("Cumulative Probability"));
    figure->set_log_x();

    figure->write_to_file(file_path);
}

}  // namespace plots
}  // namespace stat_bench
