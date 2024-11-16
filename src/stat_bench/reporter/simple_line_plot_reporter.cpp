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
 * \brief Implementation of SimpleLinePlotReporter class.
 */
#include "stat_bench/reporter/simple_line_plot_reporter.h"

#include <cstddef>
#include <fstream>
#include <utility>
#include <vector>

#include <fmt/core.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/util/prepare_directory.h"
#include "template/plotly_plot.h"

namespace stat_bench {
namespace reporter {

SimpleLinePlotReporter::SimpleLinePlotReporter(std::string prefix)
    : prefix_(std::move(prefix)) {
    renderer_.load_from_text("plotly_plot", plotly_plot);
}

void SimpleLinePlotReporter::experiment_starts(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void SimpleLinePlotReporter::experiment_finished(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void SimpleLinePlotReporter::measurer_starts(
    const measurer::MeasurerName& name) {
    measurer_name_ = name.str().str();
    std::size_t pos = 0;
    while ((pos = measurer_name_.find(' ', pos)) != std::string::npos) {
        measurer_name_.erase(pos, 1);
    }
}

void SimpleLinePlotReporter::measurer_finished(
    const measurer::MeasurerName& /*name*/) {
    // no operation
}

void SimpleLinePlotReporter::group_starts(const BenchmarkGroupName& /*name*/) {
    measurements_.clear();
}

void SimpleLinePlotReporter::group_finished(const BenchmarkGroupName& name) {
    nlohmann::json dataset_json{};
    auto& data_json = dataset_json["data"];
    for (const auto& measurement : measurements_) {
        nlohmann::json trace_json{};

        const std::size_t samples =
            measurement.samples() * measurement.cond().threads();
        std::vector<std::size_t> x{};
        x.reserve(samples);
        for (std::size_t i = 0; i < samples; ++i) {
            x.push_back(i + 1);
        }
        trace_json["x"] = x;

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

        trace_json["mode"] = "lines";
        trace_json["type"] = "scatter";
        trace_json["name"] = fmt::format("{} ({})",
            measurement.case_info().case_name(), measurement.cond().params());

        data_json.push_back(trace_json);
    }

    dataset_json["layout"]["title"] = measurer_name_;
    dataset_json["layout"]["xaxis"]["title"] = "Sample Index";
    dataset_json["layout"]["xaxis"]["type"] = "-";
    dataset_json["layout"]["yaxis"]["title"] = "Time [sec]";
    dataset_json["layout"]["yaxis"]["type"] = "log";
    dataset_json["layout"]["showlegend"] = true;

    dataset_json["config"]["scrollZoom"] = true;
    dataset_json["config"]["responsive"] = true;

    nlohmann::json input;
    input["title"] = measurer_name_;
    input["dataset"] = std::move(dataset_json);

    const std::string filepath =
        fmt::format(FMT_STRING("{}/{}/{}.html"), prefix_, name, measurer_name_);
    util::prepare_directory_for(filepath);
    std::ofstream stream{filepath};
    renderer_.render_to(stream, "plotly_plot", input);
}

void SimpleLinePlotReporter::case_starts(
    const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void SimpleLinePlotReporter::case_finished(
    const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void SimpleLinePlotReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    measurements_.push_back(measurement);
}

void SimpleLinePlotReporter::measurement_failed(
    const BenchmarkFullName& /*case_info*/, const BenchmarkCondition& /*cond*/,
    const std::exception_ptr& /*error*/) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
