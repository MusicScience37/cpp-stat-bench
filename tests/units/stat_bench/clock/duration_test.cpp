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
 * \brief Test of Duration class.
 */
#include "stat_bench/clock/duration.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "stat_bench/clock/monotone_clock_impl.h"

TEST_CASE("stat_bench::clock::Duration") {
    SECTION("get count") {
        const stat_bench::clock::TicksCount count = 12345;

        const auto duration = stat_bench::clock::Duration(count);

        REQUIRE(duration.count() == count);
    }

    SECTION("get as seconds") {
        const stat_bench::clock::TicksCount count =
            stat_bench::clock::impl::monotone_clock_freq() / 10;
        const double duration_sec = 0.1;
        const auto duration = stat_bench::clock::Duration(count);

        REQUIRE_THAT(
            duration.seconds(), Catch::Matchers::WithinRel(duration_sec));
    }
}
