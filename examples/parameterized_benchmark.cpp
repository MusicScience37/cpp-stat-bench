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
 * \brief Example of a parameterized benchmark.
 */
#include <stat_bench/benchmark_macros.h>

[[nodiscard]] auto fibonacci(int number) -> int;

// Define a fixture to define parameters.
class FibonacciFixture : public stat_bench::FixtureBase {
public:
    FibonacciFixture() {
        // Define a parameter.
        add_param<int>("number")
            // Add values to be tested.
            ->add(10)
            ->add(15);
    }
};

// Define a benchmark with a fixture.
// The first argument is the fixture class,
// the second argument is the name of the group of benchmarks,
// and the third argument is the name of the case of the benchmark.
STAT_BENCH_CASE_F(FibonacciFixture, "Fibonacci", "fibonacci") {
    const int number =
        // Get the value of the parameter from the current context object.
        stat_bench::current_invocation_context().get_param<int>("number");
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
