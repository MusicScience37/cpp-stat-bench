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
#include <iostream>
#include <memory>

#include "stat_bench/bench/benchmark_case_registry.h"
#include "stat_bench/bench/i_benchmark_case.h"
#include "stat_bench/bench/invocation_context.h"
#include "stat_bench/runner.h"

[[nodiscard]] auto fibonacci(std::uint64_t number) -> std::uint64_t {
    if (number < 2) {
        return 1;
    }
    return fibonacci(number - 1) + fibonacci(number - 2);
}

// TODO: use macros.
class TestFibonacci10 final : public stat_bench::bench::IBenchmarkCase {
public:
    TestFibonacci10() : info_("Fibonacci", "Fibonacci10") {}

    [[nodiscard]] auto info() const noexcept
        -> const stat_bench::bench::BenchmarkCaseInfo& override {
        return info_;
    }

    void invoke(stat_bench::bench::InvocationContext& context) override;

private:
    stat_bench::bench::BenchmarkCaseInfo info_;
};

void TestFibonacci10::invoke(stat_bench::bench::InvocationContext& context) {
    const std::uint64_t number = 10;
    context.measure([](std::size_t /*stat_bench_thread_index*/,
                        std::size_t /*stat_bench_sample_index*/,
                        std::size_t /*stat_bench_iteration_index*/) {
        (void)fibonacci(number);
    });
}

class TestFibonacci20 final : public stat_bench::bench::IBenchmarkCase {
public:
    TestFibonacci20() : info_("Fibonacci", "Fibonacci20") {}

    [[nodiscard]] auto info() const noexcept
        -> const stat_bench::bench::BenchmarkCaseInfo& override {
        return info_;
    }

    void invoke(stat_bench::bench::InvocationContext& context) override;

private:
    stat_bench::bench::BenchmarkCaseInfo info_;
};

void TestFibonacci20::invoke(stat_bench::bench::InvocationContext& context) {
    const std::uint64_t number = 20;
    context.measure([](std::size_t /*stat_bench_thread_index*/,
                        std::size_t /*stat_bench_sample_index*/,
                        std::size_t /*stat_bench_iteration_index*/) {
        (void)fibonacci(number);
    });
}

auto main() -> int {
    try {
        stat_bench::bench::BenchmarkCaseRegistry::instance().add(
            std::make_shared<TestFibonacci10>());
        stat_bench::bench::BenchmarkCaseRegistry::instance().add(
            std::make_shared<TestFibonacci20>());

        stat_bench::Runner runner;
        runner.init();
        runner.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
