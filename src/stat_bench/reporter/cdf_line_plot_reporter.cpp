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
 * \brief Implementation of CdfLinePlotReporter class.
 */
#include "stat_bench/reporter/cdf_line_plot_reporter.h"

#include <cstdio>
#include <fstream>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/util/prepare_directory.h"
#include "stat_bench/util/utf8_string.h"
#include "template/plotly_plot.h"

namespace stat_bench {
namespace reporter {

CdfLinePlotReporter::CdfLinePlotReporter(std::string prefix)
    : prefix_(std::move(prefix)) {
    renderer_.load_from_text("plotly_plot", plotly_plot);
}

void CdfLinePlotReporter::experiment_starts(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void CdfLinePlotReporter::experiment_finished(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void CdfLinePlotReporter::measurer_starts(const measurer::MeasurerName& name) {
    measurer_name_ = name.str().str();
    std::size_t pos = 0;
    while ((pos = measurer_name_.find(' ', pos)) != std::string::npos) {
        measurer_name_.erase(pos, 1);
    }
}

void CdfLinePlotReporter::measurer_finished(
    const measurer::MeasurerName& /*name*/) {
    // no operation
}

void CdfLinePlotReporter::group_starts(const BenchmarkGroupName& /*name*/) {
    measurements_.clear();
}

void CdfLinePlotReporter::group_finished(const BenchmarkGroupName& name) {
    nlohmann::json dataset_json{};
    auto& data_json = dataset_json["data"];
    for (const auto& measurement : measurements_) {
        nlohmann::json trace_json{};

        const std::vector<double>& x =
            measurement.durations_stat().sorted_samples();
        trace_json["x"] = x;

        const std::size_t samples =
            measurement.durations_stat().sorted_samples().size();
        std::vector<double> y;
        y.reserve(samples);
        for (std::size_t i = 0; i < samples; ++i) {
            y.push_back(
                static_cast<double>(i + 1) / static_cast<double>(samples));
        }
        trace_json["y"] = y;

        trace_json["mode"] = "lines";
        trace_json["type"] = "scatter";
        trace_json["name"] = fmt::format("{} ({})",
            measurement.case_info().case_name(), measurement.cond().params());

        data_json.push_back(trace_json);
    }

    const std::string title =
        fmt::format("Cumulative Distribution Function of {}", measurer_name_);

    dataset_json["layout"]["title"] = title;
    dataset_json["layout"]["xaxis"]["title"] = "Time [sec]";
    dataset_json["layout"]["xaxis"]["type"] = "log";
    dataset_json["layout"]["yaxis"]["title"] = "Cumulative Probability";
    dataset_json["layout"]["yaxis"]["type"] = "-";
    dataset_json["layout"]["showlegend"] = true;

    dataset_json["config"]["scrollZoom"] = true;
    dataset_json["config"]["responsive"] = true;

    nlohmann::json input;
    input["title"] = title;
    input["dataset"] = std::move(dataset_json);

    const std::string filepath = fmt::format(
        FMT_STRING("{}/{}/{}_cdf.html"), prefix_, name, measurer_name_);
    util::prepare_directory_for(filepath);
    std::ofstream stream{filepath};
    renderer_.render_to(stream, "plotly_plot", input);
}

void CdfLinePlotReporter::case_starts(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void CdfLinePlotReporter::case_finished(
    const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void CdfLinePlotReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    measurements_.push_back(measurement);
}

void CdfLinePlotReporter::measurement_failed(
    const BenchmarkFullName& /*case_info*/, const BenchmarkCondition& /*cond*/,
    const std::exception_ptr& /*error*/) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
