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
 * \brief Test of calc_stat function.
 */
#include "stat_bench/stat/calc_stat.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "stat_bench/clock/duration.h"

TEST_CASE("stat_bench::stat::calc_stat(Duration)") {
    using stat_bench::clock::Duration;

    SECTION("calculate") {
        constexpr std::size_t iterations = 2;
        const std::vector<std::vector<Duration>> data{
            {Duration(4.0), Duration(12.0)}, {Duration(2.0), Duration(6.0)}};

        const auto stat = stat_bench::stat::calc_stat(data, iterations);

        CHECK(stat.sorted_samples() ==
            std::vector<double>{1.0, 2.0, 3.0, 6.0});                 // NOLINT
        CHECK_THAT(stat.mean(), Catch::Matchers::WithinRel(3.0));     // NOLINT
        CHECK(stat.max() == 6.0);                                     // NOLINT
        CHECK(stat.min() == 1.0);                                     // NOLINT
        CHECK(stat.median() == 2.5);                                  // NOLINT
        CHECK(stat.variance() == 14.0 / 3.0);                         // NOLINT
        CHECK(stat.standard_deviation() == std::sqrt(14.0 / 3.0));    // NOLINT
        CHECK(stat.standard_error() == std::sqrt(14.0 / 3.0 / 4.0));  // NOLINT
    }

    SECTION("calculate for only one sample") {
        constexpr std::size_t iterations = 2;
        const std::vector<std::vector<Duration>> data{{Duration(4.0)}};

        const auto stat = stat_bench::stat::calc_stat(data, iterations);

        CHECK(stat.sorted_samples() == std::vector<double>{2.0});  // NOLINT
        CHECK_THAT(stat.mean(), Catch::Matchers::WithinRel(2.0));  // NOLINT
        CHECK(stat.max() == 2.0);                                  // NOLINT
        CHECK(stat.min() == 2.0);                                  // NOLINT
        CHECK(stat.median() == 2.0);                               // NOLINT
        CHECK(stat.variance() == 0.0);                             // NOLINT
        CHECK(stat.standard_deviation() == 0.0);                   // NOLINT
        CHECK(stat.standard_error() == 0.0);                       // NOLINT
    }

    SECTION("calculate without any samples") {
        constexpr std::size_t iterations = 2;
        const std::vector<std::vector<Duration>> data{{}};

        CHECK_THROWS(stat_bench::stat::calc_stat(data, iterations));
    }
}

TEST_CASE("stat_bench::stat::calc_stat(double)") {
    SECTION("calculate") {
        const std::vector<std::vector<double>> data{{2.0, 6.0}, {1.0, 3.0}};

        const auto stat = stat_bench::stat::calc_stat(data);

        CHECK(stat.sorted_samples() ==
            std::vector<double>{1.0, 2.0, 3.0, 6.0});                 // NOLINT
        CHECK_THAT(stat.mean(), Catch::Matchers::WithinRel(3.0));     // NOLINT
        CHECK(stat.max() == 6.0);                                     // NOLINT
        CHECK(stat.min() == 1.0);                                     // NOLINT
        CHECK(stat.median() == 2.5);                                  // NOLINT
        CHECK(stat.variance() == 14.0 / 3.0);                         // NOLINT
        CHECK(stat.standard_deviation() == std::sqrt(14.0 / 3.0));    // NOLINT
        CHECK(stat.standard_error() == std::sqrt(14.0 / 3.0 / 4.0));  // NOLINT
    }

    SECTION("calculate for only one sample") {
        const std::vector<std::vector<double>> data{{2.0}};

        const auto stat = stat_bench::stat::calc_stat(data);

        CHECK(stat.sorted_samples() == std::vector<double>{2.0});  // NOLINT
        CHECK_THAT(stat.mean(), Catch::Matchers::WithinRel(2.0));  // NOLINT
        CHECK(stat.max() == 2.0);                                  // NOLINT
        CHECK(stat.min() == 2.0);                                  // NOLINT
        CHECK(stat.median() == 2.0);                               // NOLINT
        CHECK(stat.variance() == 0.0);                             // NOLINT
        CHECK(stat.standard_deviation() == 0.0);                   // NOLINT
        CHECK(stat.standard_error() == 0.0);                       // NOLINT
    }

    SECTION("calculate for only one sample") {
        const std::vector<std::vector<double>> data{{}};

        CHECK_THROWS(stat_bench::stat::calc_stat(data));
    }
}
