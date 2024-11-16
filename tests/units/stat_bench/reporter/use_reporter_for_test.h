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
 * \brief Definition of use_reporter_for_test function.
 */
#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

#include "create_test_measurement.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/system_clock.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/reporter/i_reporter.h"

namespace stat_bench_test {

[[nodiscard]] inline auto create_duration(double sec) {
    using stat_bench::clock::Duration;
    return Duration(sec);
}

inline void use_reporter_for_test(stat_bench::reporter::IReporter* reporter) {
    using stat_bench::BenchmarkGroupName;
    using stat_bench::clock::Duration;
    using stat_bench::clock::SystemClock;
    using stat_bench::measurer::Measurement;

    reporter->experiment_starts(SystemClock::now());
    const std::string measurer_name = "Measurement1";
    reporter->measurer_starts(measurer_name);
    const std::string group1_name = "Group1";
    reporter->group_starts(BenchmarkGroupName(group1_name));

    const auto measurement1 = stat_bench_test::create_test_measurement(
        group1_name, "Case1", measurer_name,
        std::vector<std::vector<Duration>>{
            std::vector<Duration>{create_duration(1.0), create_duration(2.0)}});
    reporter->case_starts(measurement1.case_info());
    reporter->measurement_succeeded(measurement1);
    reporter->case_finished(measurement1.case_info());

    const auto measurement2 = stat_bench_test::create_test_measurement(
        group1_name, "Case2", measurer_name,
        std::vector<std::vector<Duration>>{std::vector<Duration>{
            create_duration(3.0), create_duration(4.0), create_duration(5.0)}});
    reporter->case_starts(measurement2.case_info());
    reporter->measurement_succeeded(measurement2);
    reporter->case_finished(measurement2.case_info());

    const auto measurement3 = stat_bench_test::create_test_measurement(
        group1_name, "Case3", measurer_name,
        std::vector<std::vector<Duration>>{std::vector<Duration>{Duration(0)}});
    reporter->case_starts(measurement3.case_info());
    reporter->measurement_failed(measurement3.case_info(), measurement3.cond(),
        std::make_exception_ptr(std::runtime_error("Test exception.")));
    reporter->case_finished(measurement3.case_info());

    reporter->group_finished(BenchmarkGroupName(group1_name));
    reporter->measurer_finished(measurer_name);
    reporter->experiment_finished(SystemClock::now());
}

}  // namespace stat_bench_test
