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

#include <cstddef>
#include <exception>
#include <memory>
#include <string>

#include "stat_bench/bench_impl/benchmark_case_registry.h"
#include "stat_bench/bench_impl/benchmark_group.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/clock/system_clock.h"
#include "stat_bench/clock/system_time_point.h"
#include "stat_bench/filters/composed_filter.h"
#include "stat_bench/measurer/mean_processing_time_measurer.h"
#include "stat_bench/measurer/processing_time_measurer.h"
#include "stat_bench/param/parameter_config.h"
#include "stat_bench/param/parameter_generator.h"
#include "stat_bench/reporter/compressed_msgpack_reporter.h"
#include "stat_bench/reporter/console_reporter.h"
#include "stat_bench/reporter/json_reporter.h"
#include "stat_bench/reporter/msgpack_reporter.h"
#include "stat_bench/reporter/plot_reporter.h"

namespace stat_bench {
namespace runner {

Runner::Runner(
    const Config& config, bench_impl::BenchmarkCaseRegistry& registry)
    : Runner(registry) {
    measurers_.push_back(std::make_shared<measurer::ProcessingTimeMeasurer>(
        config.processing_time_samples, config.min_warming_up_iterations,
        config.min_warming_up_duration_sec));
    measurers_.push_back(std::make_shared<measurer::MeanProcessingTimeMeasurer>(
        config.min_sample_duration_sec, config.mean_processing_time_samples,
        config.min_warming_up_iterations, config.min_warming_up_duration_sec));

    reporters_.push_back(std::make_shared<reporter::ConsoleReporter>());

    if (!config.plot_prefix.empty()) {
        reporters_.push_back(
            std::make_shared<reporter::PlotReporter>(config.plot_prefix));
    }

    if (!config.json_file_path.empty()) {
        reporters_.push_back(
            std::make_shared<reporter::JsonReporter>(config.json_file_path));
    }

    if (!config.msgpack_file_path.empty()) {
        reporters_.push_back(std::make_shared<reporter::MsgPackReporter>(
            config.msgpack_file_path));
    }

    if (!config.compressed_msgpack_file_path.empty()) {
        reporters_.push_back(
            std::make_shared<reporter::CompressedMsgPackReporter>(
                config.compressed_msgpack_file_path));
    }

    filters::ComposedFilter filter;
    for (const auto& pattern : config.include_glob) {
        filter.include_with_glob(pattern);
    }
    for (const auto& pattern : config.exclude_glob) {
        filter.exclude_with_glob(pattern);
    }
    for (const auto& regex : config.include_regex) {
        filter.include_with_regex(regex);
    }
    for (const auto& regex : config.exclude_regex) {
        filter.exclude_with_regex(regex);
    }
    registry.filter_by(filter);
}

Runner::Runner(bench_impl::BenchmarkCaseRegistry& registry)
    : registry_(registry) {}

Runner::~Runner() = default;

void Runner::run() const {
    auto time_stamp = clock::SystemClock::now();
    for (const auto& reporter : reporters_) {
        reporter->experiment_starts(time_stamp);
    }

    for (const auto& measurer : measurers_) {
        for (const auto& reporter : reporters_) {
            reporter->measurer_starts(measurer->name());
        }

        for (const auto& group : registry_.benchmarks()) {
            for (const auto& reporter : reporters_) {
                reporter->group_starts(group.name(), group.config());
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
    const std::shared_ptr<bench_impl::IBenchmarkCase>& bench_case) const {
    auto params = bench_case->params();
    auto generator = params.create_generator();

    while (true) {
        const auto cond = BenchmarkCondition(generator.generate());

        run_case_with_condition(measurer, bench_case, cond);

        if (!generator.iterate()) {
            break;
        }
    }
}

void Runner::run_case_with_condition(
    const std::shared_ptr<measurer::IMeasurer>& measurer,
    const std::shared_ptr<bench_impl::IBenchmarkCase>& bench_case,
    const BenchmarkCondition& cond) const {
    for (const auto& reporter : reporters_) {
        reporter->case_starts(bench_case->info());
    }

    constexpr std::size_t threads = 1;
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
