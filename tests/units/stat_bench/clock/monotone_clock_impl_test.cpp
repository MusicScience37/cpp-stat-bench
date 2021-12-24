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
 * \brief Test of functions for monotone clocks.
 */
#include "stat_bench/clock/monotone_clock_impl.h"

#include <chrono>
#include <thread>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating.hpp>

TEST_CASE("stat_bench::clock::impl::monotone_clock_now") {
    SECTION("measure duration") {
        constexpr unsigned int duration_ms = 100;
        constexpr double duration_sec = 0.1;

        const stat_bench::clock::TicksCount start =
            stat_bench::clock::impl::monotone_clock_now();
        std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
        const stat_bench::clock::TicksCount end =
            stat_bench::clock::impl::monotone_clock_now();

        const stat_bench::clock::TicksCount actual_duration_ticks = end - start;
        const double actual_duration_sec =
            static_cast<double>(actual_duration_ticks) /
            static_cast<double>(stat_bench::clock::impl::monotone_clock_freq());
        constexpr double tol = 0.5;
        REQUIRE_THAT(actual_duration_sec,
            Catch::Matchers::WithinRel(duration_sec, tol));  // NOLINT
    }
}

TEST_CASE("stat_bench::clock::impl::monotone_clock_res") {
    SECTION("get resolution") {
        REQUIRE(stat_bench::clock::impl::monotone_clock_res() > 0);
    }
}
