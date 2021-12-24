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
 * \brief Test of Statistics class.
 */
#include "stat_bench/util/statistics.h"

#include <cmath>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>

TEST_CASE("stat_bench::util::Statistics") {
    SECTION("calculate") {
        const std::vector<double> data{2.0, 6.0, 1.0};

        stat_bench::util::Statistics stat;
        stat.clear();
        stat.reserve(data.size());
        for (double val : data) {
            stat.add(val);
        }
        stat.calc();

        const std::vector<double> sorted_data{1.0, 2.0, 6.0};
        REQUIRE(stat.sorted_samples() == sorted_data);         // NOLINT
        REQUIRE(stat.mean() == 3.0);                           // NOLINT
        REQUIRE(stat.max() == 6.0);                            // NOLINT
        REQUIRE(stat.min() == 1.0);                            // NOLINT
        REQUIRE(stat.variance() == 7.0);                       // NOLINT
        REQUIRE(stat.standard_deviation() == std::sqrt(7.0));  // NOLINT
    }

    SECTION("calculate for only one sample") {
        constexpr double val = 3.14;
        const std::vector<double> data{val};

        stat_bench::util::Statistics stat;
        stat.clear();
        stat.reserve(data.size());
        for (double val : data) {
            stat.add(val);
        }
        stat.calc();

        REQUIRE(stat.sorted_samples() == data);     // NOLINT
        REQUIRE(stat.mean() == val);                // NOLINT
        REQUIRE(stat.max() == val);                 // NOLINT
        REQUIRE(stat.min() == val);                 // NOLINT
        REQUIRE(stat.variance() == 0.0);            // NOLINT
        REQUIRE(stat.standard_deviation() == 0.0);  // NOLINT
    }

    SECTION("calculate for no sample") {
        stat_bench::util::Statistics stat;
        REQUIRE_THROWS(stat.calc());
    }
}
