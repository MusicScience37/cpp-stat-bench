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

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/do_not_optimize.h"
#include "stat_bench/fixture_base.h"
#include "stat_bench/invocation_context.h"
#include "stat_bench/param/parameter_value_vector.h"
#include "stat_bench/stat/custom_stat_output.h"

class Fixture : public stat_bench::FixtureBase {
public:
    Fixture() {
        // NOLINTNEXTLINE
        add_param<std::uint64_t>("number")->add(20)->add(30);
    }

    void setup(stat_bench::InvocationContext& context) override {
        number_ = context.get_param<std::size_t>("number");
        throughput_stat_ = context.add_custom_stat("throughput_stat",
            stat_bench::stat::CustomOutputAnalysisType::rate_per_sec);
    }

    void tear_down(stat_bench::InvocationContext& context) override {
        context.add_custom_output("processed_numbers",
            static_cast<double>(context.samples()) *
                static_cast<double>(context.iterations()));
    }

protected:
    std::uint64_t number_{0};

    std::shared_ptr<stat_bench::stat::CustomStatOutput> throughput_stat_{};
};

static constexpr auto duration = std::chrono::milliseconds(10);

STAT_BENCH_CASE_F(Fixture, "FibonacciParametrized", "Fibonacci") {
    STAT_BENCH_MEASURE_INDEXED(
        thread_index, sample_index, /*iteration_index*/) {
        std::this_thread::sleep_for(duration);
        throughput_stat_->add(thread_index, sample_index, 1.0);
    };
}

STAT_BENCH_MAIN
