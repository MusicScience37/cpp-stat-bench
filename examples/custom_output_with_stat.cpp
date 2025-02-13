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
 * \brief Example of a benchmark with a custom output with statistics.
 */
#include <random>

#include <stat_bench/benchmark_macros.h>

#include "stat_bench/current_invocation_context.h"

[[nodiscard]] double approx_pi(int num_points);

// Define a fixture to define parameters.
class ApproxPiFixture : public stat_bench::FixtureBase {
public:
    ApproxPiFixture() {
        // Define a parameter.
        add_param<int>("num_points")
            // Add values to be tested.
            ->add(100)
            ->add(1000)
            ->add(10000);
    }
};

// Define a benchmark with a fixture.
// The first argument is the fixture class,
// the second argument is the name of the group of benchmarks,
// and the third argument is the name of the case of the benchmark.
STAT_BENCH_CASE_F(ApproxPiFixture, "ApproxPi", "approx_pi") {
    const int num_points =
        // Get the value of the parameter from the current context object.
        stat_bench::current_invocation_context().get_param<int>("num_points");

    constexpr double expected = 3.14159265358979323846;

    // Define a custom output with statistics.
    // Without options, the output is the mean value.
    auto error_output =
        stat_bench::current_invocation_context().add_custom_stat("error");

    // Measure the processing time with indices of threads and samples.
    // Thread index is always zero in this case,
    // because this benchmark has no configuration for multi-threading.
    STAT_BENCH_MEASURE_INDEXED(
        thread_index, sample_index, /*iteration_index*/) {
        const double approx = approx_pi(num_points);
        const double error = std::abs(approx - expected);
        // Set the value to the custom output.
        error_output->add(thread_index, sample_index, error);
    };
}

// Define main function. (Required once in an executable.)
STAT_BENCH_MAIN

double approx_pi(int num_points) {
    std::mt19937_64 engine(std::random_device{}());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    int num_inside = 0;
    for (int i = 0; i < num_points; ++i) {
        const double x = dist(engine);
        const double y = dist(engine);
        if (x * x + y * y <= 1.0) {
            ++num_inside;
        }
    }

    return 4.0 * static_cast<double>(num_inside) /
        static_cast<double>(num_points);
}
