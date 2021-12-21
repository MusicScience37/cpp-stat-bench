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
#include "stat_bench/runner.h"

#include <exception>

#include "stat_bench/bench/benchmark_case_registry.h"
#include "stat_bench/bench/benchmark_condition.h"
#include "stat_bench/clock/system_clock.h"
#include "stat_bench/measurer/mean_processing_time_measurer.h"
#include "stat_bench/measurer/processing_time_measurer.h"
#include "stat_bench/reporter/console_reporter.h"

namespace stat_bench {

Runner::Runner() = default;

void Runner::init() {
    // TODO: configuration from command line arguments.

    constexpr std::size_t max_processing_time_measurer_samples = 100;
    measurers_.push_back(std::make_shared<measurer::ProcessingTimeMeasurer>(
        max_processing_time_measurer_samples));

    constexpr std::size_t mean_processing_time_measurer_samples = 30;
    constexpr double min_sample_duration_sec = 0.03;
    measurers_.push_back(std::make_shared<measurer::MeanProcessingTimeMeasurer>(
        min_sample_duration_sec, mean_processing_time_measurer_samples));

    reporters_.push_back(std::make_shared<reporter::ConsoleReporter>());
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

}  // namespace stat_bench
