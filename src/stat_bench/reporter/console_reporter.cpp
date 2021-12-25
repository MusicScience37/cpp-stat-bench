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
 * \brief Implementation of ConsoleReporter class.
 */
#include "stat_bench/reporter/console_reporter.h"

#include <fmt/format.h>

#include "stat_bench/clock/monotone_clock_impl.h"

namespace stat_bench {
namespace reporter {

ConsoleReporter::ConsoleReporter(std::FILE* file) : file_(file) {}

void ConsoleReporter::experiment_starts(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, "Benchmark start at {}\n\n", time_stamp);

    fmt::print(file_, "Time resolution: {:.3e} sec.\n\n",
        static_cast<double>(clock::impl::monotone_clock_res()) /
            static_cast<double>(clock::impl::monotone_clock_freq()));

    std::fflush(file_);
}

void ConsoleReporter::experiment_finished(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, "Benchmark finished at {}\n", time_stamp);
    std::fflush(file_);
}

void ConsoleReporter::measurer_starts(const std::string& name) {
    fmt::print(file_, "## {}\n\n", name);
    std::fflush(file_);
}

void ConsoleReporter::measurer_finished(const std::string& name) {
    fmt::print(file_, "\n");
    std::fflush(file_);
}

static constexpr const char* console_table_format =
    "{:<30}{:>10d}{:>10d}{:>15.5f}{:>15.5f}\n";
static constexpr const char* console_table_format_label =
    "{:<30}{:>10}{:>10}{:>15}{:>15}\n";
static constexpr const char* console_table_format_error = "{:<30}{}\n";

void ConsoleReporter::group_starts(const std::string& name) {
    fmt::print(file_, "### {}\n\n", name);
    fmt::print(file_, console_table_format_label, "", "Iterations", "Samples",
        "Mean [ms]", "Max [ms]");
    fmt::print(file_, "{:-<82}\n", "");
    std::fflush(file_);
}

void ConsoleReporter::group_finished(const std::string& /*name*/) {
    // no operation
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
    constexpr double sec_to_ms = 1e+3;
    fmt::print(file_, console_table_format, measurement.case_info(),
        measurement.iterations(), measurement.samples(),
        measurement.durations_stat().mean() * sec_to_ms,
        measurement.durations_stat().max() * sec_to_ms);
    std::fflush(file_);
}

void ConsoleReporter::measurement_failed(
    const bench::BenchmarkCaseInfo& case_info,
    const bench::BenchmarkCondition& cond, const std::exception_ptr& error) {
    try {
        std::rethrow_exception(error);
    } catch (const std::exception& e) {
        fmt::print(file_, console_table_format_error, case_info, e.what());
    }
    std::fflush(file_);
}

}  // namespace reporter
}  // namespace stat_bench
