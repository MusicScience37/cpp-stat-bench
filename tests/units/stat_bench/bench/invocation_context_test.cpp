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
 * \brief Definition of InvocationContext class.
 */
#include "stat_bench/bench/invocation_context.h"

#include <mutex>
#include <tuple>
#include <utility>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::bench::InvocationContext") {
    SECTION("construct") {
        constexpr std::size_t threads = 1;
        constexpr std::size_t iterations = 7;
        constexpr std::size_t samples = 13;

        const stat_bench::bench::InvocationContext context{
            stat_bench::bench::BenchmarkCondition(threads), iterations,
            samples};

        REQUIRE(context.threads() == threads);
        REQUIRE(context.iterations() == iterations);
        REQUIRE(context.samples() == samples);
    }

    SECTION("measure durations") {
        constexpr std::size_t threads = 1;
        constexpr std::size_t iterations = 7;
        constexpr std::size_t samples = 13;
        stat_bench::bench::InvocationContext context{
            stat_bench::bench::BenchmarkCondition(threads), iterations,
            samples};

        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>
            invocations;
        context.measure(
            [&invocations](std::size_t thread_index, std::size_t sample_index,
                std::size_t iteration_index) {
                invocations.emplace_back(
                    thread_index, sample_index, iteration_index);
            });

        REQUIRE(invocations.size() == threads * iterations * samples);
        std::size_t invocation_index = 0;
        for (std::size_t sample_index = 0; sample_index < samples;
             ++sample_index) {
            INFO("sample_index = " << sample_index);
            for (std::size_t iteration_index = 0; iteration_index < iterations;
                 ++iteration_index) {
                INFO("iteration_index = " << iteration_index);
                INFO("invocation_index = " << invocation_index);

                REQUIRE(std::get<0>(invocations.at(invocation_index)) == 0);
                REQUIRE(std::get<1>(invocations.at(invocation_index)) ==
                    sample_index);
                REQUIRE(std::get<2>(invocations.at(invocation_index)) ==
                    iteration_index);

                ++invocation_index;
            }
        }

        const auto durations = context.durations();
        REQUIRE(durations.size() == threads);
        REQUIRE(durations.at(0).size() == samples);
    }

    SECTION("measure durations with threads") {
        constexpr std::size_t threads = 2;
        constexpr std::size_t iterations = 7;
        constexpr std::size_t samples = 13;
        stat_bench::bench::InvocationContext context{
            stat_bench::bench::BenchmarkCondition(threads), iterations,
            samples};

        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>
            invocations;
        std::mutex mutex;
        context.measure(
            [&invocations, &mutex](std::size_t thread_index,
                std::size_t sample_index, std::size_t iteration_index) {
                std::unique_lock<std::mutex> lock(mutex);
                invocations.emplace_back(
                    thread_index, sample_index, iteration_index);
            });

        REQUIRE(invocations.size() == threads * iterations * samples);
        std::size_t invocation_index = 0;
        for (std::size_t thread_index = 0; thread_index < threads;
             ++thread_index) {
            for (std::size_t sample_index = 0; sample_index < samples;
                 ++sample_index) {
                INFO("sample_index = " << sample_index);
                for (std::size_t iteration_index = 0;
                     iteration_index < iterations; ++iteration_index) {
                    INFO("iteration_index = " << iteration_index);
                    INFO("invocation_index = " << invocation_index);

                    REQUIRE(std::get<0>(invocations.at(invocation_index)) ==
                        thread_index);
                    REQUIRE(std::get<1>(invocations.at(invocation_index)) ==
                        sample_index);
                    REQUIRE(std::get<2>(invocations.at(invocation_index)) ==
                        iteration_index);

                    ++invocation_index;
                }
            }
        }

        const auto durations = context.durations();
        REQUIRE(durations.size() == threads);
        REQUIRE(durations.at(0).size() == samples);
    }
}
