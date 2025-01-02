/*
 * Copyright 2021 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of ViolinPlotReporter class.
 */
#include "stat_bench/reporter/violin_plot_reporter.h"

#include <cmath>
#include <cstdio>
#include <fstream>
#include <limits>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "../plots/template/plotly_plot.h"
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/util/prepare_directory.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace reporter {

ViolinPlotReporter::ViolinPlotReporter(std::string prefix)
    : prefix_(std::move(prefix)) {
    renderer_.load_from_text("plotly_plot", plotly_plot);
}

void ViolinPlotReporter::experiment_starts(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void ViolinPlotReporter::experiment_finished(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void ViolinPlotReporter::measurer_starts(const measurer::MeasurerName& name) {
    measurer_name_ = name.str().str();
    std::size_t pos = 0;
    while ((pos = measurer_name_.find(' ', pos)) != std::string::npos) {
        measurer_name_.erase(pos, 1);
    }
}

void ViolinPlotReporter::measurer_finished(
    const measurer::MeasurerName& /*name*/) {
    // no operation
}

void ViolinPlotReporter::group_starts(const BenchmarkGroupName& /*name*/) {
    measurements_.clear();
}

void ViolinPlotReporter::group_finished(const BenchmarkGroupName& name) {
    nlohmann::json dataset_json{};
    auto& data_json = dataset_json["data"];
    double min_duration = std::numeric_limits<double>::max();
    double max_duration = std::numeric_limits<double>::min();
    for (const auto& measurement : measurements_) {
        nlohmann::json trace_json{};

        const std::size_t samples =
            measurement.durations_stat().sorted_samples().size();

        std::vector<double> y;
        y.reserve(samples);
        const double inv_iterations =
            1.0 / static_cast<double>(measurement.iterations());
        for (const auto& durations_per_thread : measurement.durations()) {
            for (const auto& duration : durations_per_thread) {
                y.push_back(duration.seconds() * inv_iterations);
            }
        }
        trace_json["y"] = y;

        trace_json["type"] = "violin";
        trace_json["name"] = fmt::format("{} ({})",
            measurement.case_info().case_name(), measurement.cond().params());
        trace_json["box"]["visible"] = true;
        trace_json["meanline"]["visible"] = true;
        trace_json["points"] = "outliers";

        data_json.push_back(trace_json);

        const double cur_min_duration = measurement.durations_stat().min();
        const double cur_max_duration = measurement.durations_stat().max();
        if (cur_min_duration < min_duration) {
            min_duration = cur_min_duration;
        }
        if (cur_max_duration > max_duration) {
            max_duration = cur_max_duration;
        }
    }

    const std::string title = fmt::format("Violin Plot of {}", measurer_name_);

    constexpr double min_duration_limit = 1e-9;
    if (min_duration < min_duration_limit) {
        min_duration = min_duration_limit;
    }
    constexpr double margin_coeff = 1.5;
    min_duration /= margin_coeff;
    max_duration *= margin_coeff;

    dataset_json["layout"]["title"] = title;
    dataset_json["layout"]["yaxis"]["title"] = "Time [sec]";
    dataset_json["layout"]["yaxis"]["type"] = "log";
    dataset_json["layout"]["yaxis"]["constrain"] = "range";
    dataset_json["layout"]["yaxis"]["range"] =
        std::vector<double>{std::log10(min_duration), std::log10(max_duration)};
    dataset_json["layout"]["showlegend"] = true;

    dataset_json["config"]["scrollZoom"] = true;
    dataset_json["config"]["responsive"] = true;

    nlohmann::json input;
    input["title"] = title;
    input["dataset"] = std::move(dataset_json);

    const std::string filepath = fmt::format(
        FMT_STRING("{}/{}/{}_violin.html"), prefix_, name, measurer_name_);
    util::prepare_directory_for(filepath);
    std::ofstream stream{filepath};
    renderer_.render_to(stream, "plotly_plot", input);
}

void ViolinPlotReporter::case_starts(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void ViolinPlotReporter::case_finished(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void ViolinPlotReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    measurements_.push_back(measurement);
}

void ViolinPlotReporter::measurement_failed(
    const BenchmarkFullName& /*case_info*/, const BenchmarkCondition& /*cond*/,
    const std::exception_ptr& /*error*/) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
