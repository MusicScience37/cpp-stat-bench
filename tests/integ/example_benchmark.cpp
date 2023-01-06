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
 * \brief Benchmark of fibonacci.
 */
#include <cstdint>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/do_not_optimize.h"

[[nodiscard]] auto fibonacci(std::uint64_t number) -> std::uint64_t {
    if (number < 2) {
        return 1;
    }
    return fibonacci(number - 1) + fibonacci(number - 2);
}

STAT_BENCH_CASE("Fibonacci", "Fibonacci") {
    std::uint64_t number = 30;  // NOLINT
    STAT_BENCH_MEASURE() {
        stat_bench::do_not_optimize(number);
        stat_bench::do_not_optimize(fibonacci(number));
    };
}

STAT_BENCH_MAIN
