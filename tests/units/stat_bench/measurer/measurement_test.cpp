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
 * \brief Test of Measurement class.
 */
#include "stat_bench/measurer/measurement.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::measurer::Measurement") {
    using stat_bench::clock::Duration;

    SECTION("construct") {
        const auto info = stat_bench::bench::BenchmarkCaseInfo("group", "case");
        const auto cond = stat_bench::bench::BenchmarkCondition(5);
        const auto measurer_name = std::string("measurer");
        const std::size_t iterations = 7;
        const std::size_t samples = 11;
        const auto durations = std::vector<std::vector<Duration>>{
            std::vector<Duration>{Duration(1), Duration(2)},
            std::vector<Duration>{Duration(3), Duration(4)}};

        const auto measurement = stat_bench::measurer::Measurement(
            info, cond, measurer_name, iterations, samples, durations);

        REQUIRE(measurement.case_info().group_name() == info.group_name());
        REQUIRE(measurement.case_info().case_name() == info.case_name());
        REQUIRE(measurement.cond().threads() == cond.threads());
        REQUIRE(measurement.measurer_name() == measurer_name);
        REQUIRE(measurement.iterations() == iterations);
        REQUIRE(measurement.samples() == samples);
        REQUIRE(measurement.durations().size() == 2);
        REQUIRE(measurement.durations().at(0).size() == 2);
        REQUIRE(measurement.durations().at(0).at(0).count() == 1);
        REQUIRE(measurement.durations().at(0).at(1).count() == 2);
        REQUIRE(measurement.durations().at(1).size() == 2);
        REQUIRE(measurement.durations().at(1).at(0).count() == 3);
        REQUIRE(measurement.durations().at(1).at(1).count() == 4);
        REQUIRE(measurement.durations_stat().sorted_samples().size() == 4);
    }
}
