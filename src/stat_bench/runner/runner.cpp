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
 * \brief Implementation of Runner class.
 */
#include "stat_bench/runner/runner.h"

#include <exception>
#include <stdexcept>

#include "stat_bench/bench/benchmark_case_registry.h"
#include "stat_bench/bench/benchmark_condition.h"
#include "stat_bench/clock/system_clock.h"
#include "stat_bench/measurer/mean_processing_time_measurer.h"
#include "stat_bench/measurer/processing_time_measurer.h"
#include "stat_bench/reporter/console_reporter.h"
#include "stat_bench/reporter/simple_line_plot_reporter.h"

namespace stat_bench {
namespace runner {

Runner::Runner() {
    cli_ |= lyra::opt(config_.show_help)["-h"]["--help"]("Show this help.");
    cli_ |= lyra::opt(config_.processing_time_samples, "num")["--samples"](
        "Number of samples for measurements of processing time.")
                .choices([](std::size_t val) { return val > 0; });
    cli_ |= lyra::opt(
        config_.mean_processing_time_samples, "num")["--mean_samples"](
        "Number of samples for measurements of mean processing time.")
                .choices([](std::size_t val) { return val > 0; });
    cli_ |= lyra::opt(
        config_.min_sample_duration_sec, "num")["--min_sample_duration"](
        "minimum duration of a sample for measurement of mean processing time. "
        "[sec]")
                .choices([](double val) { return val > 0.0; });
}

Runner::~Runner() = default;

void Runner::parse_cli(int argc, const char** argv) {
    const auto result = cli_.parse(lyra::args{argc, argv});
    if (!result) {
        throw std::runtime_error(result.message());
    }
}

void Runner::init() {
    measurers_.push_back(std::make_shared<measurer::ProcessingTimeMeasurer>(
        config_.processing_time_samples));

    measurers_.push_back(std::make_shared<measurer::MeanProcessingTimeMeasurer>(
        config_.min_sample_duration_sec, config_.mean_processing_time_samples));

    reporters_.push_back(std::make_shared<reporter::ConsoleReporter>());

    reporters_.push_back(
        std::make_shared<reporter::SimpleLinePlotReporter>(""));
}

void Runner::run(const bench::BenchmarkCaseRegistry& registry) const {
    auto time_stamp = clock::SystemClock::now();
    for (const auto& reporter : reporters_) {
        reporter->experiment_starts(time_stamp);
    }

    for (const auto& measurer : measurers_) {
        for (const auto& reporter : reporters_) {
            reporter->measurer_starts(measurer->name());
        }

        for (const auto& group : registry.benchmarks()) {
            for (const auto& reporter : reporters_) {
                reporter->group_starts(group.name());
            }

            for (const auto& bench_case : group.cases()) {
                run_case(measurer, bench_case);
            }

            for (const auto& reporter : reporters_) {
                reporter->group_finished(group.name());
            }
        }

        for (const auto& reporter : reporters_) {
            reporter->measurer_finished(measurer->name());
        }
    }

    time_stamp = clock::SystemClock::now();
    for (const auto& reporter : reporters_) {
        reporter->experiment_finished(time_stamp);
    }
}

void Runner::run_case(const std::shared_ptr<measurer::IMeasurer>& measurer,
    const std::shared_ptr<bench::IBenchmarkCase>& bench_case) const {
    for (const auto& reporter : reporters_) {
        reporter->case_starts(bench_case->info());
    }

    constexpr std::size_t threads = 1;
    const auto cond = bench::BenchmarkCondition(threads);
    std::exception_ptr error_in_reporter;
    try {
        const auto measurement = measurer->measure(bench_case.get(), cond);

        try {
            for (const auto& reporter : reporters_) {
                reporter->measurement_succeeded(measurement);
            }
        } catch (...) {
            error_in_reporter = std::current_exception();
        }
    } catch (...) {
        const auto error = std::current_exception();
        for (const auto& reporter : reporters_) {
            reporter->measurement_failed(bench_case->info(), cond, error);
        }
    }
    if (error_in_reporter) {
        std::rethrow_exception(error_in_reporter);
    }

    for (const auto& reporter : reporters_) {
        reporter->case_finished(bench_case->info());
    }
}

}  // namespace runner
}  // namespace stat_bench
