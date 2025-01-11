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

#include <cstdint>
#include <cstdio>
#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/format.h>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/monotone_time_point.h"
#include "stat_bench/custom_output_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/stat/custom_stat_output.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/util/utf8_string.h"
#include "stat_bench/version.h"

namespace stat_bench {
namespace reporter {

namespace {

void print_line(std::FILE* file, char c) {
    constexpr std::size_t line_length = 120;
    fmt::print(file, "{}\n", std::string(line_length, c));
}

}  // namespace

ConsoleReporter::ConsoleReporter(std::FILE* file) : file_(file) {}

void ConsoleReporter::experiment_starts(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, FMT_STRING("cpp-stat-bench {}.{}.{}\n\n"),
        STAT_BENCH_VERSION_MAJOR, STAT_BENCH_VERSION_MINOR,
        STAT_BENCH_VERSION_PATCH);

    fmt::print(file_, FMT_STRING("Benchmark start at {}\n\n"), time_stamp);

    fmt::print(file_, FMT_STRING("Time resolution: {:.3e} sec.\n\n"),
        clock::MonotoneTimePoint::resolution().seconds());

    (void)std::fflush(file_);
}

void ConsoleReporter::experiment_finished(
    const clock::SystemTimePoint& time_stamp) {
    fmt::print(file_, FMT_STRING("Benchmark finished at {}\n"), time_stamp);
    (void)std::fflush(file_);
}

void ConsoleReporter::measurer_starts(const measurer::MeasurerName& name) {
    print_line(file_, '=');
    fmt::print(file_, FMT_STRING("{}\n"), name);
    print_line(file_, '=');
    fmt::print(file_, "\n");
    (void)std::fflush(file_);
}

void ConsoleReporter::measurer_finished(const measurer::MeasurerName& name) {
    // no operation
    (void)name;
}

namespace {

auto format_duration(double val) -> std::string {
    constexpr double sec_to_us = 1e+6;
    constexpr double tol = 1e-4;
    if (val < tol) {
        return fmt::format(FMT_STRING("{:.4f}"), val * sec_to_us);
    }
    return fmt::format(FMT_STRING("{}"),
        fmt::group_digits(static_cast<std::uint64_t>(val * sec_to_us)));
}

}  // namespace

#define CONSOLE_TABLE_FORMAT "{:<58}  {:>10} {:>7}  {:>9} {:>9} {:>9} "
#define CONSOLE_TABLE_FORMAT_ERROR "{:<58}  {}"

void ConsoleReporter::group_starts(const BenchmarkGroupName& name,
    const bench_impl::BenchmarkGroupConfig& /*config*/) {
    fmt::print(file_, FMT_STRING(">> {}\n"), name);
    fmt::print(file_, FMT_STRING(CONSOLE_TABLE_FORMAT "{}\n"), "", "", "",
        "Time [us]", "", "", "");
    fmt::print(file_, FMT_STRING(CONSOLE_TABLE_FORMAT "{}\n"), "", "Iterations",
        "Samples", "Mean", "Std. Err.", "Max", "Custom Outputs (mean)");
    print_line(file_, '-');
    (void)std::fflush(file_);
}

void ConsoleReporter::group_finished(const BenchmarkGroupName& /*name*/) {
    fmt::print(file_, "\n");
    (void)std::fflush(file_);
}

void ConsoleReporter::case_starts(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void ConsoleReporter::case_finished(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

namespace {

auto format_case_name_with_params(const BenchmarkFullName& case_info,
    const BenchmarkCondition& cond) -> std::string {
    if (cond.params().empty()) {
        return case_info.case_name().str().str();
    }
    return fmt::format(
        FMT_STRING("{} ({}) "), case_info.case_name(), cond.params());
}

}  // namespace

void ConsoleReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    fmt::print(file_, FMT_STRING(CONSOLE_TABLE_FORMAT),
        format_case_name_with_params(
            measurement.case_info(), measurement.cond()),
        measurement.iterations(), measurement.samples(),
        format_duration(measurement.durations_stat().mean()),
        format_duration(measurement.durations_stat().standard_error()),
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
    (void)std::fflush(file_);
}

void ConsoleReporter::measurement_failed(const BenchmarkFullName& case_info,
    const BenchmarkCondition& cond, const std::exception_ptr& error) {
    try {
        std::rethrow_exception(error);
    } catch (const std::exception& e) {
        fmt::print(file_, fmt::fg(fmt::color::red),
            FMT_STRING(CONSOLE_TABLE_FORMAT_ERROR),
            format_case_name_with_params(case_info, cond), e.what());
    }
    fmt::print(file_, "\n");
    (void)std::fflush(file_);
}

}  // namespace reporter
}  // namespace stat_bench
