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
 * \brief Test of ThreadableInvoker class.
 */
#include "stat_bench/bench_impl/threadable_invoker.h"

#include <mutex>
#include <stdexcept>
#include <string>
#include <tuple>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::bench_impl::ThreadableInvoker") {
    SECTION("measure using single thread") {
        constexpr std::size_t threads = 1;
        constexpr std::size_t iterations = 7;
        constexpr std::size_t samples = 13;
        constexpr std::size_t warm_up_samples = 5;

        const stat_bench::bench_impl::ThreadableInvoker invoker{
            threads, iterations, samples, warm_up_samples};

        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>
            invocations;
        const auto durations = invoker.measure(
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

        REQUIRE(durations.size() == threads);
        REQUIRE(durations.at(0).size() == samples - warm_up_samples);
    }

    SECTION("error in single thread measurement") {
        constexpr std::size_t threads = 1;
        constexpr std::size_t iterations = 7;
        constexpr std::size_t samples = 13;
        constexpr std::size_t warm_up_samples = 5;

        const stat_bench::bench_impl::ThreadableInvoker invoker{
            threads, iterations, samples, warm_up_samples};

        REQUIRE_THROWS(invoker.measure(
            [](std::size_t thread_index, std::size_t sample_index,
                std::size_t iteration_index) {
                throw std::runtime_error("Test exception.");
            }));
    }

    SECTION("measure using multiple threads") {
        constexpr std::size_t threads = 3;
        constexpr std::size_t iterations = 7;
        constexpr std::size_t samples = 13;
        constexpr std::size_t warm_up_samples = 5;

        const stat_bench::bench_impl::ThreadableInvoker invoker{
            threads, iterations, samples, warm_up_samples};

        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>
            invocations;
        std::mutex mutex;
        const auto durations = invoker.measure(
            [&invocations, &mutex](std::size_t thread_index,
                std::size_t sample_index, std::size_t iteration_index) {
                std::unique_lock<std::mutex> lock(mutex);
                invocations.emplace_back(
                    thread_index, sample_index, iteration_index);
            });

        REQUIRE(invocations.size() == threads * iterations * samples);

        REQUIRE(durations.size() == threads);
        REQUIRE(durations.at(0).size() == samples - warm_up_samples);
    }

    SECTION("error in single thread measurement") {
        constexpr std::size_t threads = 3;
        constexpr std::size_t iterations = 7;
        constexpr std::size_t samples = 13;
        constexpr std::size_t warm_up_samples = 5;

        const stat_bench::bench_impl::ThreadableInvoker invoker{
            threads, iterations, samples, warm_up_samples};

        REQUIRE_THROWS(invoker.measure(
            [](std::size_t thread_index, std::size_t sample_index,
                std::size_t iteration_index) {
                throw std::runtime_error("Test exception.");
            }));
    }

    SECTION("invalid arguments") {
        REQUIRE_THROWS(
            (void)stat_bench::bench_impl::ThreadableInvoker(0, 1, 1, 0));
        REQUIRE_THROWS(
            (void)stat_bench::bench_impl::ThreadableInvoker(1, 0, 1, 0));
        REQUIRE_THROWS(
            (void)stat_bench::bench_impl::ThreadableInvoker(1, 1, 0, 0));
        REQUIRE_THROWS(
            (void)stat_bench::bench_impl::ThreadableInvoker(1, 1, 1, 1));
    }
}
