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

#include <memory>
#include <utility>
#include <vector>

#include <fmt/color.h>
#include <fmt/format.h>

#include "stat_bench/clock/monotone_clock_impl.h"
#include "stat_bench/stat/custom_stat_output.h"
#include "stat_bench/stat/statistics.h"

namespace stat_bench {
namespace reporter {

ConsoleReporter::ConsoleReporter(std::FILE* file) : file_(file) {}

void ConsoleReporter::experiment_starts(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, FMT_STRING("Benchmark start at {}\n\n"), time_stamp);

    fmt::print(file_, FMT_STRING("Time resolution: {:.3e} sec.\n\n"),
        static_cast<double>(clock::impl::monotone_clock_res()) /
            static_cast<double>(clock::impl::monotone_clock_freq()));

    std::fflush(file_);
}

void ConsoleReporter::experiment_finished(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, FMT_STRING("Benchmark finished at {}\n"), time_stamp);
    std::fflush(file_);
}

void ConsoleReporter::measurer_starts(const std::string& name) {
    fmt::print(file_, FMT_STRING("## {}\n\n"), name);
    std::fflush(file_);
}

void ConsoleReporter::measurer_finished(const std::string& name) {
    fmt::print(file_, "\n");
    std::fflush(file_);
}

namespace {

auto format_duration(double val) -> std::string {
    constexpr double sec_to_ms = 1e+3;
    constexpr double tol = 1e-3;
    if (val < tol) {
        return fmt::format(FMT_STRING("{:.3e}"), val * sec_to_ms);
    }
    return fmt::format(FMT_STRING("{:.3f}"), val * sec_to_ms);
}

}  // namespace

#define CONSOLE_TABLE_FORMAT "{:<50} {:>10} {:>8} {:>12} {:>12} "
#define CONSOLE_TABLE_FORMAT_ERROR "{:<50} {}"

void ConsoleReporter::group_starts(const std::string& name) {
    fmt::print(file_, FMT_STRING("### {}\n\n"), name);
    fmt::print(file_, FMT_STRING(CONSOLE_TABLE_FORMAT "{}\n"), "", "Iterations",
        "Samples", "Mean [ms]", "Max [ms]", "Custom Outputs (mean)");
    fmt::print(file_, FMT_STRING("{:-<120}\n"), "");
    std::fflush(file_);
}

void ConsoleReporter::group_finished(const std::string& /*name*/) {
    // no operation
}

void ConsoleReporter::case_starts(
    const bench::BenchmarkFullName& /*case_info*/) {
    // no operation
}

void ConsoleReporter::case_finished(
    const bench::BenchmarkFullName& /*case_info*/) {
    // no operation
}

void ConsoleReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    fmt::print(file_, FMT_STRING(CONSOLE_TABLE_FORMAT),
        fmt::format(FMT_STRING("{} ({}) "), measurement.case_info().case_name(),
            measurement.cond().params()),
        measurement.iterations(), measurement.samples(),
        format_duration(measurement.durations_stat().mean()),
        format_duration(measurement.durations_stat().max()));
    for (std::size_t i = 0; i < measurement.custom_stat_outputs().size(); ++i) {
        fmt::print(file_, FMT_STRING("{}={:.3e}, "),
            measurement.custom_stat_outputs().at(i)->name(),
            measurement.custom_stat().at(i).mean());
    }
    for (const auto& out : measurement.custom_outputs()) {
        fmt::print(file_, FMT_STRING("{}={:.3e}, "), out.first, out.second);
    }
    fmt::print(file_, "\n");
    std::fflush(file_);
}

void ConsoleReporter::measurement_failed(
    const bench::BenchmarkFullName& case_info,
    const bench::BenchmarkCondition& cond, const std::exception_ptr& error) {
    try {
        std::rethrow_exception(error);
    } catch (const std::exception& e) {
        fmt::print(file_, fmt::fg(fmt::color::red),
            FMT_STRING(CONSOLE_TABLE_FORMAT_ERROR),
            fmt::format(
                FMT_STRING("{} ({}) "), case_info.case_name(), cond.params()),
            e.what());
    }
    fmt::print(file_, "\n");
    std::fflush(file_);
}

}  // namespace reporter
}  // namespace stat_bench
