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
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/fixture_base.h"
#include "stat_bench/invocation_context.h"
#include "stat_bench/param/parameter_value_vector.h"
#include "stat_bench/plot_option.h"
#include "stat_bench/stat/custom_stat_output.h"

class FibonacciFixture : public stat_bench::FixtureBase {
public:
    FibonacciFixture() {
        // NOLINTNEXTLINE
        add_param<std::uint64_t>("number")->add(10)->add(20)->add(30);
    }

    void setup(stat_bench::InvocationContext& context) override {
        number_ = context.get_param<std::size_t>("number");
    }

    void tear_down(stat_bench::InvocationContext& context) override {
        context.add_custom_output("result", static_cast<double>(result_));
    }

protected:
    std::uint64_t number_{0};
    std::uint64_t result_{0};
};

[[nodiscard]] auto fibonacci(std::uint64_t number) -> std::uint64_t {
    if (number < 2) {
        return 1;
    }
    return fibonacci(number - 1) + fibonacci(number - 2);
}

STAT_BENCH_CASE_F(FibonacciFixture, "FibonacciParametrized", "Fibonacci") {
    STAT_BENCH_MEASURE() { result_ = fibonacci(number_); };
}

STAT_BENCH_GROUP("FibonacciParametrized")
    .add_parameter_to_time_plot("number")
    .add_parameter_to_output_plot(
        "number", "result", stat_bench::PlotOption::log_output)
    .add_time_to_output_by_parameter_plot(
        "number", "result", stat_bench::PlotOption::log_output);

class VectorPushBackFixture : public stat_bench::FixtureBase {
public:
    VectorPushBackFixture() {
        // NOLINTNEXTLINE
        add_param<std::size_t>("size")->add(100)->add(1000)->add(10000);
        add_param<bool>("reserve")->add(false)->add(true);
    }

    void setup(stat_bench::InvocationContext& context) override {
        size_ = context.get_param<std::size_t>("size");
        reserve_ = context.get_param<bool>("reserve");
        throughput_stat_ = context.add_custom_stat("throughput_stat",
            stat_bench::stat::CustomOutputAnalysisType::rate_per_sec);
    }

    void tear_down(stat_bench::InvocationContext& context) override {
        context.add_custom_output("processed_numbers",
            static_cast<double>(context.samples()) *
                static_cast<double>(context.iterations()));
    }

protected:
    std::size_t size_{0};
    bool reserve_{false};
    std::shared_ptr<stat_bench::stat::CustomStatOutput> throughput_stat_{};
};

STAT_BENCH_CASE_F(
    VectorPushBackFixture, "VectorPushBackParametrized", "VectorPushBack") {
    STAT_BENCH_MEASURE_INDEXED(
        thread_index, sample_index, /*iteration_index*/) {
        std::vector<std::size_t> vec;
        if (reserve_) {
            vec.reserve(size_);
        }
        for (std::size_t i = 0; i < size_; ++i) {
            vec.push_back(i);
        }
        throughput_stat_->add(thread_index, sample_index, 1.0);
    };
}

STAT_BENCH_GROUP("VectorPushBackParametrized")
    .add_parameter_to_time_plot("size", stat_bench::PlotOption::log_parameter)
    .add_parameter_to_output_plot("size", "throughput_stat",
        stat_bench::PlotOption::log_parameter |
            stat_bench::PlotOption::log_output)
    .add_time_to_output_by_parameter_plot(
        "size", "throughput_stat", stat_bench::PlotOption::log_output)
    .add_parameter_to_output_plot("size", "processed_numbers",
        stat_bench::PlotOption::log_parameter |
            stat_bench::PlotOption::log_output);

STAT_BENCH_MAIN
