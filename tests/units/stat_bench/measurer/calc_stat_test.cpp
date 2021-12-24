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
#include "stat_bench/measurer/calc_stat.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating.hpp>

#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/monotone_clock_impl.h"

TEST_CASE("stat_bench::measurer::calc_stat(Duration)") {
    using stat_bench::clock::Duration;

    SECTION("calculate") {
        const stat_bench::clock::TicksCount freq = Duration::freq();
        const std::vector<std::vector<Duration>> data{
            {Duration(2 * freq), Duration(6 * freq)},
            {Duration(freq), Duration(3 * freq)}};

        const auto stat = stat_bench::measurer::calc_stat(data);

        REQUIRE(stat.sorted_samples() ==
            std::vector<double>{1.0, 2.0, 3.0, 6.0});                // NOLINT
        REQUIRE_THAT(stat.mean(), Catch::Matchers::WithinRel(3.0));  // NOLINT
    }
}

TEST_CASE("stat_bench::measurer::calc_stat(double)") {
    SECTION("calculate") {
        const std::vector<std::vector<double>> data{{2.0, 6.0}, {1.0, 3.0}};

        const auto stat = stat_bench::measurer::calc_stat(data);

        REQUIRE(stat.sorted_samples() ==
            std::vector<double>{1.0, 2.0, 3.0, 6.0});                // NOLINT
        REQUIRE_THAT(stat.mean(), Catch::Matchers::WithinRel(3.0));  // NOLINT
    }
}
