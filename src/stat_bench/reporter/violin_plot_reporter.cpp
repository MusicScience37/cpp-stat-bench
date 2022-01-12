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
#include <fstream>
#include <limits>

#include <fmt/core.h>
#include <fmt/format.h>

#include "stat_bench/reporter/render_template.h"
#include "stat_bench/reporter/template/violin.html.h"
#include "stat_bench/util/prepare_directory.h"

namespace stat_bench {
namespace reporter {

ViolinPlotReporter::ViolinPlotReporter(std::string prefix)
    : prefix_(std::move(prefix)) {}

void ViolinPlotReporter::experiment_starts(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void ViolinPlotReporter::experiment_finished(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void ViolinPlotReporter::measurer_starts(const std::string& name) {
    measurer_name_ = name;
    std::size_t pos = 0;
    while ((pos = measurer_name_.find(' ', pos)) != std::string::npos) {
        measurer_name_.erase(pos, 1);
    }
}

void ViolinPlotReporter::measurer_finished(const std::string& /*name*/) {
    // no operation
}

void ViolinPlotReporter::group_starts(const std::string& /*name*/) {
    data_buf_.clear();
    data_buf_.push_back('[');
    min_duration_ = std::numeric_limits<double>::max();
    max_duration_ = std::numeric_limits<double>::min();
}

void ViolinPlotReporter::group_finished(const std::string& name) {
    data_buf_.push_back(']');

    constexpr double min_duration_limit = 1e-9;
    if (min_duration_ < min_duration_limit) {
        min_duration_ = min_duration_limit;
    }
    constexpr double margin_coeff = 1.5;
    min_duration_ /= margin_coeff;
    max_duration_ *= margin_coeff;

    const std::string contents = render_template(violin,
        std::unordered_map<std::string, std::string>{
            {"{{PLOT_NAME}}", fmt::format("Violin Plot of {}", measurer_name_)},
            {"{{Y_TITLE}}", "Time [sec]"}, {"{{Y_TYPE}}", "log"},
            {"\"{{Y_MIN}}\"",
                fmt::format(FMT_STRING("{}"), std::log10(min_duration_))},
            {"\"{{Y_MAX}}\"",
                fmt::format(FMT_STRING("{}"), std::log10(max_duration_))},
            {"\"{{DATA}}\"", std::string(data_buf_.data(), data_buf_.size())}});

    const std::string filepath = fmt::format(
        FMT_STRING("{}{}_{}_violin.html"), prefix_, name, measurer_name_);
    util::prepare_directory_for(filepath);
    std::ofstream stream{filepath};
    stream << contents;
}

void ViolinPlotReporter::case_starts(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void ViolinPlotReporter::case_finished(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void ViolinPlotReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    const std::size_t samples =
        measurement.durations_stat().sorted_samples().size();

    const std::string name = fmt::format(FMT_STRING("{} ({})"),
        measurement.case_info().case_name(), measurement.cond().params());

    std::vector<double> y;
    y.reserve(samples);
    const double inv_iterations =
        1.0 / static_cast<double>(measurement.iterations());
    for (const auto& durations_per_thread : measurement.durations()) {
        for (const auto& duration : durations_per_thread) {
            y.push_back(duration.seconds() * inv_iterations);
        }
    }

    fmt::format_to(std::back_inserter(data_buf_), FMT_STRING(R"***({{
    y: [{}],
    type: "violin",
    name: "{}",
    box: {{
        visible: true,
    }},
    meanline: {{
        visible: true,
    }},
    points: "outliers",
}},)***"),
        fmt::join(y, ", "), name);

    const double min_duration = measurement.durations_stat().min();
    const double max_duration = measurement.durations_stat().max();
    if (min_duration < min_duration_) {
        min_duration_ = min_duration;
    }
    if (max_duration > max_duration_) {
        max_duration_ = max_duration;
    }
}

void ViolinPlotReporter::measurement_failed(
    const bench::BenchmarkCaseInfo& /*case_info*/,
    const bench::BenchmarkCondition& /*cond*/,
    const std::exception_ptr& /*error*/) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
