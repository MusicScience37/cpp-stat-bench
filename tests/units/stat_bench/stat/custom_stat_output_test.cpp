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

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

TEST_CASE("stat_bench::stat::CustomStatOutput") {
    SECTION("construct") {
        const std::string name = "CustomStat";
        constexpr std::size_t threads = 2;
        constexpr std::size_t samples = 3;
        constexpr std::size_t iterations = 4;

        stat_bench::stat::CustomStatOutput output{
            name, threads, samples, iterations};

        REQUIRE(output.name() == name);
    }

    SECTION("calculate statistics") {
        const std::string name = "CustomStat";
        constexpr std::size_t threads = 2;
        constexpr std::size_t samples = 3;
        constexpr std::size_t iterations = 4;

        stat_bench::stat::CustomStatOutput output{
            name, threads, samples, iterations};
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

        const auto stat = output.stat();
        REQUIRE_THAT(stat.mean(), Catch::Matchers::WithinRel(4.0));  // NOLINT
        REQUIRE_THAT(stat.sorted_samples(),
            Catch::Matchers::Approx(
                std::vector<double>{1.0, 2.0, 3.0, 5.0, 6.0, 7.0}));  // NOLINT
    }
}
