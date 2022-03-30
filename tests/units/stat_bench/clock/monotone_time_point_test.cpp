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
 * \brief Test of MonotoneTimePoint class.
 */
#include "stat_bench/clock/monotone_time_point.h"

#include <string>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::clock::MonotoneTimePoint") {
    SECTION("calculate a duration") {
        constexpr stat_bench::clock::TicksCount start_ticks = 123;
        constexpr stat_bench::clock::TicksCount duration_ticks = 37;
        constexpr stat_bench::clock::TicksCount end_ticks =
            start_ticks + duration_ticks;

        const auto start = stat_bench::clock::MonotoneTimePoint(start_ticks);
        const auto end = stat_bench::clock::MonotoneTimePoint(end_ticks);
        const stat_bench::clock::Duration duration = end - start;

        REQUIRE(duration.count() == duration_ticks);
    }
}
