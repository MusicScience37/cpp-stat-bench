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
 * \brief Implementation of PlotReporter class.
 */
#include "stat_bench/reporter/plot_reporter.h"

#include <cstddef>
#include <filesystem>
#include <memory>
#include <utility>

#include <fmt/format.h>

#include "stat_bench/bench_impl/benchmark_group_config.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/plots/box_plot.h"
#include "stat_bench/plots/cdf_line_plot.h"
#include "stat_bench/plots/samples_line_plot.h"
#include "stat_bench/plots/violin_plot.h"
#include "stat_bench/util/escape_for_file_name.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace reporter {

PlotReporter::PlotReporter(std::string prefix)
    : prefix_(std::move(prefix)), group_name_(""), measurement_type_("") {
    builtin_plots_.push_back(std::make_shared<plots::SamplesLinePlot>());
    builtin_plots_.push_back(std::make_shared<plots::CdfLinePlot>());
    builtin_plots_.push_back(std::make_shared<plots::ViolinPlot>());
    builtin_plots_.push_back(std::make_shared<plots::BoxPlot>());
}

void PlotReporter::experiment_starts(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void PlotReporter::experiment_finished(
    const clock::SystemTimePoint& /*time_stamp*/) {
    // no operation
}

void PlotReporter::group_starts(const BenchmarkGroupName& name,
    const bench_impl::BenchmarkGroupConfig& config) {
    group_name_ = name;
    group_plots_ = config.plots();
}

void PlotReporter::group_finished(const BenchmarkGroupName& /*name*/) {
    // no operation
}

void PlotReporter::measurement_type_starts(
    const measurer::MeasurementType& type) {
    measurement_type_ = type;

    std::string measurement_type_without_space = measurement_type_.str().str();
    std::size_t pos = 0;
    while ((pos = measurement_type_without_space.find(' ', pos)) !=
        std::string::npos) {
        measurement_type_without_space.erase(pos, 1);
    }

    measurement_type_for_file_paths_ = util::escape_for_file_name(
        util::Utf8String(measurement_type_without_space));
}

void PlotReporter::measurement_type_finished(
    const measurer::MeasurementType& /*type*/) {
    const auto process_plot = [this](
                                  const std::shared_ptr<plots::IPlot>& plot) {
        const std::string file_path = fmt::format("{}/{}/{}_{}.html", prefix_,
            util::escape_for_file_name(group_name_.str()),
            measurement_type_for_file_paths_,
            util::escape_for_file_name(plot->name_for_file()));
        std::filesystem::create_directories(
            std::filesystem::path(file_path).parent_path());
        plot->write(measurement_type_, group_name_, measurements_, file_path);
    };
    for (const auto& plot : builtin_plots_) {
        process_plot(plot);
    }
    for (const auto& plot : group_plots_) {
        process_plot(plot);
    }

    measurements_.clear();
}

void PlotReporter::case_starts(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void PlotReporter::case_finished(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void PlotReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    measurements_.push_back(measurement);
}

void PlotReporter::measurement_failed(const BenchmarkFullName& /*case_info*/,
    const BenchmarkCondition& /*cond*/, const std::exception_ptr& /*error*/) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
