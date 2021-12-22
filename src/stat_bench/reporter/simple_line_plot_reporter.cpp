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

#include <fstream>

#include <fmt/core.h>
#include <fmt/format.h>

#include "stat_bench/reporter/render_template.h"
#include "stat_bench/reporter/template/line2d.html.h"

namespace stat_bench {
namespace reporter {

SimpleLinePlotReporter::SimpleLinePlotReporter(std::string prefix)
    : prefix_(std::move(prefix)) {}

void SimpleLinePlotReporter::experiment_starts(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void SimpleLinePlotReporter::experiment_finished(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void SimpleLinePlotReporter::measurer_starts(const std::string& name) {
    measurer_name_ = name;
    std::size_t pos = 0;
    while ((pos = measurer_name_.find(' ', pos)) != std::string::npos) {
        measurer_name_.erase(pos, 1);
    }
}

void SimpleLinePlotReporter::measurer_finished(const std::string& /*name*/) {
    // no operation
}

void SimpleLinePlotReporter::group_starts(const std::string& /*name*/) {
    data_buf_.clear();
    data_buf_.push_back('[');
}

void SimpleLinePlotReporter::group_finished(const std::string& name) {
    data_buf_.push_back(']');

    const std::string contents = render_template(line2d,
        std::unordered_map<std::string, std::string>{
            {"{{PLOT_NAME}}", measurer_name_}, {"{{X_TITLE}}", "Sample Index"},
            {"{{X_TYPE}}", "-"}, {"{{Y_TITLE}}", "Time [sec]"},
            {"{{Y_TYPE}}", "log"},
            {"\"{{DATA}}\"", std::string(data_buf_.data(), data_buf_.size())}});

    const std::string filepath =
        fmt::format(FMT_STRING("{}{}_{}.html"), prefix_, name, measurer_name_);
    std::ofstream stream{filepath};
    stream << contents;
}

void SimpleLinePlotReporter::case_starts(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void SimpleLinePlotReporter::case_finished(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void SimpleLinePlotReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    const std::size_t samples = measurement.samples();
    std::vector<std::size_t> x;
    x.reserve(samples);
    for (std::size_t i = 0; i < samples; ++i) {
        x.push_back(i + 1);
    }

    auto y = std::vector<double>(samples, 0.0);
    const double inv_iterations =
        1.0 / static_cast<double>(measurement.iterations());
    for (const auto& durations_per_thread : measurement.durations()) {
        for (std::size_t i = 0; i < samples; ++i) {
            y.at(i) += durations_per_thread.at(i).seconds() * inv_iterations;
        }
    }
    const double inv_threads =
        1.0 / static_cast<double>(measurement.durations().size());
    for (auto& val : y) {
        val *= inv_threads;
    }

    fmt::format_to(std::back_inserter(data_buf_), FMT_STRING(R"***({{
    x: [{}],
    y: [{}],
    mode: "lines",
    type: "scatter",
    name: "{} (threads={})",
}},)***"),
        fmt::join(x, ", "), fmt::join(y, ", "), measurement.case_info(),
        measurement.cond().threads());
}

void SimpleLinePlotReporter::measurement_failed(
    const bench::BenchmarkCaseInfo& /*case_info*/,
    const bench::BenchmarkCondition& /*cond*/,
    const std::exception_ptr& /*error*/) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
