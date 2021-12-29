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
 * \brief Test of ProcessingTimeMeasurer class.
 */
#include "stat_bench/measurer/processing_time_measurer.h"

#include <chrono>
#include <memory>
#include <thread>

#include <catch2/catch_test_macros.hpp>

#include "../bench/mock_benchmark_case.h"
#include "../param/create_ordinary_parameter_dict.h"
#include "stat_bench/bench/benchmark_case_info.h"
#include "stat_bench/bench/benchmark_condition.h"

TEST_CASE("stat_bench::measurer::ProcessingTimeMeasurer") {
    constexpr std::size_t samples = 3;
    constexpr std::size_t min_warming_up_iterations = 5;
    constexpr double min_warming_up_duration_sec = 0.01;
    const auto measurer =
        std::make_shared<stat_bench::measurer::ProcessingTimeMeasurer>(
            samples, min_warming_up_iterations, min_warming_up_duration_sec);

    SECTION("get name") { REQUIRE(measurer->name() == "Processing Time"); }

    SECTION("measure") {
        stat_bench_test::bench::MockBenchmarkCase bench_case;
        const auto info = stat_bench::bench::BenchmarkCaseInfo("group", "case");
        const auto cond = stat_bench::bench::BenchmarkCondition(
            1, stat_bench_test::param::create_ordinary_parameter_dict());

        // NOLINTNEXTLINE
        ALLOW_CALL(bench_case, info()).RETURN(info);
        REQUIRE_CALL(bench_case, execute(trompeloeil::_))
            .TIMES(AT_LEAST(1))
            // NOLINTNEXTLINE
            .SIDE_EFFECT(_1.measure(
                [](std::size_t /*thread_index*/, std::size_t /*sample_index*/,
                    std::size_t /*iteration_index*/) {
                    // NOLINTNEXTLINE
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }));

        const auto result = measurer->measure(&bench_case, cond);
        REQUIRE(result.case_info().group_name() == info.group_name());
        REQUIRE(result.case_info().case_name() == info.case_name());
        REQUIRE(result.cond().threads() == cond.threads());
        REQUIRE(result.measurer_name() == "Processing Time");
        REQUIRE(result.iterations() > 0);
        REQUIRE(result.samples() == samples);
        REQUIRE(result.durations().size() == 1);
        REQUIRE(result.durations().at(0).size() == result.samples());
    }
}
