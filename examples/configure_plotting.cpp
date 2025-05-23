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
 * \brief Example of a benchmark with configurations of plotting.
 */
#include <stat_bench/benchmark_macros.h>

[[nodiscard]] double approx_exp(double x, int num_terms);

// Define a fixture to define parameters.
class ApproxExpFixture : public stat_bench::FixtureBase {
public:
    ApproxExpFixture() {
        // Define a parameter.
        add_param<int>("num_terms")
            // Add values to be tested.
            ->add(1)
            ->add(2)
            ->add(5)
            ->add(10);
    }
};

// Define a benchmark with a fixture.
// The first argument is the fixture class,
// the second argument is the name of the group of benchmarks,
// and the third argument is the name of the case of the benchmark.
STAT_BENCH_CASE_F(ApproxExpFixture, "ApproxExp", "approx_exp") {
    constexpr double x = 1.0;
    const int num_terms =
        // Get the value of the parameter from the current context object.
        stat_bench::current_invocation_context().get_param<int>("num_terms");

    STAT_BENCH_MEASURE() { return approx_exp(x, num_terms); };

    const double expected = std::exp(x);
    const double approx = approx_exp(x, num_terms);
    const double error = std::abs(approx - expected);
    // Set a custom output.
    stat_bench::current_invocation_context().add_custom_output("error", error);
}

// Configure the group of benchmarks.
// This can be placed anywhere in the executable.
STAT_BENCH_GROUP("ApproxExp")
    // Here you can configure plotting.
    // In this example, some of available plots are used.

    // Add a line plot.
    // * X-axis: Parameter "num_terms".
    // * Y-axis: Processing time. (Log scale is used always.)
    .add_parameter_to_time_line_plot("num_terms")

    // Add a line plot.
    // * X-axis: Parameter "num_terms".
    // * Y-axis: Custom output "error" in log scale.
    // Custom outputs without or with statistics can be specified similarly.
    .add_parameter_to_output_line_plot(
        "num_terms", "error", stat_bench::PlotOptions().log_output(true))

    // Add a line plot.
    // * X-axis: Processing time. (Log scale is used always.)
    // * Y-axis: Custom output "error" in log scale.
    // This plot shows the change of the above two values while parameter
    // "num_terms" changes.
    // This is useful to see efficiency of algorithms.
    .add_time_to_output_by_parameter_line_plot(
        "num_terms", "error", stat_bench::PlotOptions().log_output(true));

// Define main function. (Required once in an executable.)
STAT_BENCH_MAIN

double approx_exp(double x, int num_terms) {
    double result = 1.0;
    double term = 1.0;
    for (int i = 1; i < num_terms; ++i) {
        term *= x / i;
        result += term;
    }
    return result;
}
