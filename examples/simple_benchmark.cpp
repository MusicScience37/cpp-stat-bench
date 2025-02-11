/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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
 * \brief Example of a simple benchmark.
 */
#include <stat_bench/benchmark_macros.h>

[[nodiscard]] auto fibonacci(int number) -> int;

// Define a benchmark.
// First argument is the name of the group of benchmarks,
// and the second argument is the name of the case of the benchmark.
STAT_BENCH_CASE("Fibonacci", "fibonacci(10)") {
    const int number = 10;
    // Measure the time to invoke a function.
    // The return value is handled by cpp-stat-bench library to prevent
    // compilers from optimizing out the function call.
    STAT_BENCH_MEASURE() { return fibonacci(number); };
}

// Define another benchmark in the same group.
STAT_BENCH_CASE("Fibonacci", "fibonacci(15)") {
    const int number = 15;
    STAT_BENCH_MEASURE() { return fibonacci(number); };
}

// Define main function. (Required once in an executable.)
STAT_BENCH_MAIN

auto fibonacci(int number) -> int {
    if (number < 2) {
        return 1;
    }
    return fibonacci(number - 1) + fibonacci(number - 2);
}
