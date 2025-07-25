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
 * \brief Test of CustomStatOutput class.
 */
#include "stat_bench/stat/custom_stat_output.h"

#include <cmath>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_tostring.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include "stat_bench/clock/duration.h"
#include "stat_bench/custom_output_name.h"

TEST_CASE("stat_bench::stat::CustomStatOutput") {
    using stat_bench::CustomOutputName;

    SECTION("construct") {
        const auto name = CustomOutputName("CustomStat");
        constexpr std::size_t threads = 2;
        constexpr std::size_t samples = 3;
        constexpr std::size_t warming_up_samples = 2;
        constexpr std::size_t iterations = 4;

        stat_bench::stat::CustomStatOutput output{name, threads, samples,
            warming_up_samples, iterations,
            stat_bench::stat::CustomOutputAnalysisType::mean};

        REQUIRE(output.name() == name);
    }

    SECTION("calculate statistics") {
        const auto name = CustomOutputName("CustomStat");
        constexpr std::size_t threads = 2;
        constexpr std::size_t samples = 3;
        constexpr std::size_t warming_up_samples = 1;
        constexpr std::size_t iterations = 4;

        stat_bench::stat::CustomStatOutput output{name, threads, samples,
            warming_up_samples, iterations,
            stat_bench::stat::CustomOutputAnalysisType::mean};
        output.add(0, 0, 1.0);  // NOLINT
        output.add(0, 0, 1.0);  // NOLINT
        output.add(0, 0, 1.0);  // NOLINT
        output.add(0, 0, 1.0);  // NOLINT
        output.add(0, 1, 1.0);  // NOLINT
        output.add(0, 1, 3.0);  // NOLINT
        output.add(0, 1, 1.0);  // NOLINT
        output.add(0, 1, 3.0);  // NOLINT
        output.add(0, 2, 3.0);  // NOLINT
        output.add(0, 2, 3.0);  // NOLINT
        output.add(0, 2, 3.0);  // NOLINT
        output.add(0, 2, 3.0);  // NOLINT
        output.add(1, 0, 5.0);  // NOLINT
        output.add(1, 0, 5.0);  // NOLINT
        output.add(1, 0, 5.0);  // NOLINT
        output.add(1, 0, 5.0);  // NOLINT
        output.add(1, 1, 5.0);  // NOLINT
        output.add(1, 1, 5.0);  // NOLINT
        output.add(1, 1, 7.0);  // NOLINT
        output.add(1, 1, 7.0);  // NOLINT
        output.add(1, 2, 7.0);  // NOLINT
        output.add(1, 2, 7.0);  // NOLINT
        output.add(1, 2, 7.0);  // NOLINT
        output.add(1, 2, 7.0);  // NOLINT

        std::vector<std::vector<stat_bench::clock::Duration>> durations{
            {stat_bench::clock::Duration(2.0),
                stat_bench::clock::Duration(1.0)}};
        output.preprocess(durations);
        const auto stat = output.stat();
        REQUIRE_THAT(stat.mean(), Catch::Matchers::WithinRel(4.5));  // NOLINT
        REQUIRE_THAT(stat.sorted_samples(),
            Catch::Matchers::Approx(
                std::vector<double>{2.0, 3.0, 6.0, 7.0}));  // NOLINT
    }

    SECTION("calculate statistics using rate per seconds") {
        const auto name = CustomOutputName("CustomStat");
        constexpr std::size_t threads = 1;
        constexpr std::size_t samples = 3;
        constexpr std::size_t warming_up_samples = 1;
        constexpr std::size_t iterations = 1;

        stat_bench::stat::CustomStatOutput output{name, threads, samples,
            warming_up_samples, iterations,
            stat_bench::stat::CustomOutputAnalysisType::rate_per_sec};
        output.add(0, 0, 1.0);  // NOLINT
        output.add(0, 1, 1.0);  // NOLINT
        output.add(0, 2, 2.0);  // NOLINT

        std::vector<std::vector<stat_bench::clock::Duration>> durations{
            {stat_bench::clock::Duration(2.0),
                stat_bench::clock::Duration(1.0)}};
        output.preprocess(durations);
        const auto stat = output.stat();
        REQUIRE_THAT(stat.sorted_samples(),
            Catch::Matchers::Approx(std::vector<double>{0.5, 2.0}));  // NOLINT
    }

    SECTION(
        "calculate statistics using rate per seconds when some durations are "
        "zero") {
        const auto name = CustomOutputName("CustomStat");
        constexpr std::size_t threads = 1;
        constexpr std::size_t samples = 3;
        constexpr std::size_t warming_up_samples = 1;
        constexpr std::size_t iterations = 1;

        stat_bench::stat::CustomStatOutput output{name, threads, samples,
            warming_up_samples, iterations,
            stat_bench::stat::CustomOutputAnalysisType::rate_per_sec};
        output.add(0, 0, 1.0);  // NOLINT
        output.add(0, 1, 1.0);  // NOLINT
        output.add(0, 2, 2.0);  // NOLINT

        std::vector<std::vector<stat_bench::clock::Duration>> durations{
            {stat_bench::clock::Duration(0.0),
                stat_bench::clock::Duration(1.0)}};
        output.preprocess(durations);
        const auto stat = output.stat();
        CHECK(std::isfinite(stat.unsorted_samples().at(0)));
        CHECK(std::isfinite(stat.unsorted_samples().at(1)));
        CHECK(std::isfinite(stat.sorted_samples().at(0)));
        CHECK(std::isfinite(stat.sorted_samples().at(1)));
        CHECK(std::isfinite(stat.mean()));
        CHECK(std::isfinite(stat.max()));
        CHECK(std::isfinite(stat.min()));
        CHECK(std::isfinite(stat.median()));
        CHECK(std::isfinite(stat.variance()));
        CHECK(std::isfinite(stat.standard_deviation()));
        CHECK(std::isfinite(stat.standard_error()));
    }
}
