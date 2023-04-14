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
// IWYU pragma: no_include  <stddef.h>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <memory>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/do_not_optimize.h"
#include "stat_bench/fixture_base.h"
#include "stat_bench/invocation_context.h"
#include "stat_bench/param/parameter_value_vector.h"

[[nodiscard]] auto fibonacci(std::uint64_t number) -> std::uint64_t {
    if (number < 2) {
        return 1;
    }
    return fibonacci(number - 1) + fibonacci(number - 2);
}

class Fixture : public stat_bench::FixtureBase {
public:
    Fixture() {
        // NOLINTNEXTLINE
        add_param<std::uint64_t>("number")->add(10)->add(20)->add(30);
    }

    void setup(stat_bench::InvocationContext& context) override {
        number_ = context.get_param<std::size_t>("number");
    }

protected:
    std::uint64_t number_{0};
};

STAT_BENCH_CASE_F(Fixture, "Fibonacci", "Fibonacci") {
    STAT_BENCH_MEASURE() {
        stat_bench::do_not_optimize(number_);
        stat_bench::do_not_optimize(fibonacci(number_));
    };
}

STAT_BENCH_MAIN
