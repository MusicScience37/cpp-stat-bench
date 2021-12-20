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
 * \brief Definition of ConsoleReporter class.
 */
#include "stat_bench/reporter/console_reporter.h"

#include <fmt/format.h>

namespace stat_bench {
namespace reporter {

ConsoleReporter::ConsoleReporter(std::FILE* file) : file_(file) {}

void ConsoleReporter::experiment_starts(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, "Benchmark start at {}\n\n", time_stamp);
    std::fflush(file_);
}

void ConsoleReporter::experiment_finished(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, "Benchmark finished at {}\n\n", time_stamp);
}

void ConsoleReporter::measurer_starts(const std::string& name) {
    fmt::print(file_, "## {}\n\n", name);
}

void ConsoleReporter::measurer_finished(const std::string& name) {
    fmt::print(file_, "\n");
}

static constexpr const char* console_table_format =
    "{:<30}{:>10d}{:>10d}{:>10.3f}{:>10.3f}\n";
static constexpr const char* console_table_format_error = "{:<30}{}\n";

void ConsoleReporter::group_starts(const std::string& name) {
    fmt::print(file_, "### {}\n\n", name);
    fmt::print(file_, console_table_format, "", "Iterations", "Samples",
        "Mean [ms]", "Max [ms]");
    fmt::print(file_, "{:-<72}", "");
}

void ConsoleReporter::group_finished(const std::string& /*name*/) {
    fmt::print(file_, "\n");
}

void ConsoleReporter::case_starts(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void ConsoleReporter::case_finished(
    const bench::BenchmarkCaseInfo& /*case_info*/) {
    // no operation
}

void ConsoleReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    double sum_ms = 0.0;
    double max_ms = 0.0;
    std::size_t num = 0.0;
    for (const auto& durations_per_thread : measurement.durations()) {
        for (const auto& duration : durations_per_thread) {
            const double duration_ms = duration.seconds() * 1e-3;
            sum_ms += duration_ms;
            if (duration_ms > max_ms) {
                max_ms = duration_ms;
            }
            ++num;
        }
    }
    const double mean_ms = sum_ms / static_cast<double>(num);
    fmt::print(file_, console_table_format, measurement.case_info(),
        measurement.iterations(), measurement.samples(), mean_ms, max_ms);
}

void ConsoleReporter::measurement_failed(
    const bench::BenchmarkCaseInfo& case_info,
    const bench::BenchmarkCondition& cond, const std::exception_ptr& error) {
    try {
        std::rethrow_exception(error);
    } catch (const std::exception& e) {
        fmt::print(file_, console_table_format_error, case_info, e.what());
    }
}

}  // namespace reporter
}  // namespace stat_bench
