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
#include <memory>
#include <string>

#include "stat_bench/bench_impl/benchmark_case_registry.h"
#include "stat_bench/bench_impl/benchmark_group.h"
#include "stat_bench/bench_impl/benchmark_group_config.h"
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/clock/system_clock.h"
#include "stat_bench/clock/system_time_point.h"
#include "stat_bench/filters/composed_filter.h"
#include "stat_bench/param/parameter_config.h"
#include "stat_bench/param/parameter_generator.h"
#include "stat_bench/reporter/compressed_msgpack_reporter.h"
#include "stat_bench/reporter/console_reporter.h"
#include "stat_bench/reporter/json_reporter.h"
#include "stat_bench/reporter/msgpack_reporter.h"
#include "stat_bench/reporter/plot_reporter.h"
#include "stat_bench/util/ordered_map.h"

namespace stat_bench::runner {

Runner::Runner(
    const Config& config, bench_impl::BenchmarkCaseRegistry& registry)
    : measurer_(config.min_sample_duration_sec,
          config.min_warming_up_duration_sec, config.samples,
          config.min_warming_up_iterations),
      registry_(registry) {
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

Runner::~Runner() = default;

void Runner::run() const {
    auto time_stamp = clock::SystemClock::now();
    for (const auto& reporter : reporters_) {
        reporter->experiment_starts(time_stamp);
    }

    for (const auto& group_pair : registry_.benchmarks()) {
        const auto& group = group_pair.second;
        for (const auto& reporter : reporters_) {
            reporter->group_starts(group.name(), group.config());
        }

        for (const auto& [measurement_type, measurement_config] :
            group.config().measurement_configs()) {
            for (const auto& reporter : reporters_) {
                reporter->measurement_type_starts(measurement_type);
            }

            for (const auto& bench_case_pair : group.cases()) {
                const auto& bench_case = bench_case_pair.second;
                run_case(bench_case, measurement_config);
            }

            for (const auto& reporter : reporters_) {
                reporter->measurement_type_finished(measurement_type);
            }
        }

        for (const auto& reporter : reporters_) {
            reporter->group_finished(group.name());
        }
    }

    time_stamp = clock::SystemClock::now();
    for (const auto& reporter : reporters_) {
        reporter->experiment_finished(time_stamp);
    }
}

void Runner::run_case(
    const std::shared_ptr<bench_impl::IBenchmarkCase>& bench_case,
    const MeasurementConfig& measurement_config) const {
    auto params = bench_case->params();
    auto generator = params.create_generator();

    while (true) {
        const auto condition = BenchmarkCondition(generator.generate());

        run_case_with_condition(bench_case, condition, measurement_config);

        if (!generator.iterate()) {
            break;
        }
    }
}

void Runner::run_case_with_condition(
    const std::shared_ptr<bench_impl::IBenchmarkCase>& bench_case,
    const BenchmarkCondition& condition,
    const MeasurementConfig& measurement_config) const {
    for (const auto& reporter : reporters_) {
        reporter->case_starts(bench_case->info());
    }

    std::exception_ptr error_in_reporter;
    try {
        const auto measurement =
            measurer_.measure(bench_case.get(), condition, measurement_config);

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
            reporter->measurement_failed(bench_case->info(), condition, error);
        }
    }
    if (error_in_reporter) {
        std::rethrow_exception(error_in_reporter);
    }

    for (const auto& reporter : reporters_) {
        reporter->case_finished(bench_case->info());
    }
}

}  // namespace stat_bench::runner
