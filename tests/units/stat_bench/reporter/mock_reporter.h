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
 * \brief Definition of MockReporter class.
 */
#pragma once

#include <exception>
#include <string>

#include "../../trompeloeil.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/clock/system_time_point.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/reporter/i_reporter.h"

namespace stat_bench_test {
namespace reporter {

class MockReporter final : public stat_bench::reporter::IReporter {
public:
    // NOLINTNEXTLINE
    MAKE_MOCK1(experiment_starts,
        void(const stat_bench::clock::SystemTimePoint&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(experiment_finished,
        void(const stat_bench::clock::SystemTimePoint&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(measurer_starts, void(const stat_bench::measurer::MeasurerName&),
        override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(measurer_finished,
        void(const stat_bench::measurer::MeasurerName&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(
        group_starts, void(const stat_bench::BenchmarkGroupName&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(
        group_finished, void(const stat_bench::BenchmarkGroupName&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(
        case_starts, void(const stat_bench::BenchmarkFullName&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(
        case_finished, void(const stat_bench::BenchmarkFullName&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(measurement_succeeded,
        void(const stat_bench::measurer::Measurement&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK3(measurement_failed,
        void(const stat_bench::BenchmarkFullName&,
            const stat_bench::BenchmarkCondition&,
            const std::exception_ptr& error),
        override);

    MockReporter() = default;
    MockReporter(const MockReporter&) = delete;
    MockReporter(MockReporter&&) = delete;
    auto operator=(const MockReporter&) -> MockReporter& = delete;
    auto operator=(MockReporter&&) -> MockReporter& = delete;
    ~MockReporter() override = default;
};

}  // namespace reporter
}  // namespace stat_bench_test
