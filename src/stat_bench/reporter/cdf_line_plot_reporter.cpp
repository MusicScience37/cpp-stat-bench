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

#include <fstream>

#include <fmt/core.h>
#include <fmt/format.h>

#include "stat_bench/reporter/render_template.h"
#include "stat_bench/reporter/template/line2d.html.h"
#include "stat_bench/util/prepare_directory.h"

namespace stat_bench {
namespace reporter {

CdfLinePlotReporter::CdfLinePlotReporter(std::string prefix)
    : prefix_(std::move(prefix)) {}

void CdfLinePlotReporter::experiment_starts(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void CdfLinePlotReporter::experiment_finished(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void CdfLinePlotReporter::measurer_starts(const std::string& name) {
    measurer_name_ = name;
    std::size_t pos = 0;
    while ((pos = measurer_name_.find(' ', pos)) != std::string::npos) {
        measurer_name_.erase(pos, 1);
    }
}

void CdfLinePlotReporter::measurer_finished(const std::string& /*name*/) {
    // no operation
}

void CdfLinePlotReporter::group_starts(const std::string& /*name*/) {
    data_buf_.clear();
    data_buf_.push_back('[');
}

void CdfLinePlotReporter::group_finished(const std::string& name) {
    data_buf_.push_back(']');

    const std::string contents = render_template(line2d,
        std::unordered_map<std::string, std::string>{
            {"{{PLOT_NAME}}",
                fmt::format(
                    "Cumulative Distribution Function of {}", measurer_name_)},
            {"{{X_TITLE}}", "Time [sec]"}, {"{{X_TYPE}}", "log"},
            {"{{Y_TITLE}}", "Cumulative Probability"}, {"{{Y_TYPE}}", "-"},
            {"\"{{DATA}}\"", std::string(data_buf_.data(), data_buf_.size())}});

    const std::string filepath = fmt::format(
        FMT_STRING("{}/{}/{}_cdf.html"), prefix_, name, measurer_name_);
    util::prepare_directory_for(filepath);
    std::ofstream stream{filepath};
    stream << contents;
}

void CdfLinePlotReporter::case_starts(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void CdfLinePlotReporter::case_finished(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void CdfLinePlotReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    const std::vector<double>& x =
        measurement.durations_stat().sorted_samples();
    const std::size_t samples =
        measurement.durations_stat().sorted_samples().size();
    std::vector<double> y;
    y.reserve(samples);
    for (std::size_t i = 0; i < samples; ++i) {
        y.push_back(static_cast<double>(i + 1) / static_cast<double>(samples));
    }

    fmt::format_to(std::back_inserter(data_buf_), FMT_STRING(R"***({{
    x: [{}],
    y: [{}],
    mode: "lines",
    type: "scatter",
    name: "{} ({})",
}},)***"),
        fmt::join(x, ", "), fmt::join(y, ", "),
        measurement.case_info().case_name(), measurement.cond().params());
}

void CdfLinePlotReporter::measurement_failed(
    const bench::BenchmarkCaseInfo& /*case_info*/,
    const bench::BenchmarkCondition& /*cond*/,
    const std::exception_ptr& /*error*/) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
