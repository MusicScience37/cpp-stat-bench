/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
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
 * \brief Test of groups and cases.
 */
#include <chrono>
#include <thread>

#include "stat_bench/benchmark_macros.h"

static constexpr auto duration = std::chrono::milliseconds(50);

STAT_BENCH_CASE("Group1", "Case1") {
    STAT_BENCH_MEASURE() { std::this_thread::sleep_for(duration); };
}

STAT_BENCH_CASE("Group1", "Case2") {
    STAT_BENCH_MEASURE() { std::this_thread::sleep_for(duration); };
}

STAT_BENCH_CASE("Group2", "Case3") {
    STAT_BENCH_MEASURE() { std::this_thread::sleep_for(duration); };
}

STAT_BENCH_MAIN
