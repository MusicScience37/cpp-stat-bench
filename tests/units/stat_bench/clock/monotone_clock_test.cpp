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
 * \brief Test of MonotoneClock class.
 */
#include "stat_bench/clock/monotone_clock.h"

#include <chrono>
#include <thread>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating.hpp>

TEST_CASE("stat_bench::clock::MonotoneClock") {
    SECTION("measure a duration") {
        constexpr unsigned int duration_ms = 100;
        constexpr double duration_sec = 0.1;

        const auto start = stat_bench::clock::MonotoneClock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
        const auto end = stat_bench::clock::MonotoneClock::now();

        const auto actual_duration = end - start;
        const double actual_duration_sec = actual_duration.seconds();
        constexpr double tol = 0.5;
        REQUIRE_THAT(actual_duration_sec,
            Catch::Matchers::WithinRel(duration_sec, tol));  // NOLINT
    }
}
