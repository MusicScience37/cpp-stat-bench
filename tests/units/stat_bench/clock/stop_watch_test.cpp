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
 * \brief Test of StopWatch class.
 */
#include "stat_bench/clock/stop_watch.h"

#include <chrono>
#include <thread>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating.hpp>

TEST_CASE("stat_bench::clock::StopWatch") {
    SECTION("measure a duration") {
        constexpr unsigned int duration_ms = 10;
        constexpr double duration_sec = 0.01;
        constexpr std::size_t num_laps = 7;

        stat_bench::clock::StopWatch watch;
        watch.start(num_laps);
        for (std::size_t i = 0; i < num_laps; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
            watch.lap();
        }
        const auto durations = watch.calc_durations();

        REQUIRE(durations.size() == num_laps);
        for (std::size_t i = 0; i < num_laps; ++i) {
            INFO("i = " << i);
            constexpr double tol = 0.9;
            REQUIRE_THAT(durations.at(i).seconds(),
                Catch::Matchers::WithinRel(duration_sec, tol));
        }
    }

    SECTION("lack of samples") {
        constexpr unsigned int duration_ms = 10;
        constexpr double duration_sec = 0.01;
        constexpr std::size_t num_laps = 7;

        stat_bench::clock::StopWatch watch;
        watch.start(num_laps);
        REQUIRE_THROWS(watch.calc_durations());
    }
}
