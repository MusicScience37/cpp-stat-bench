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
 * \brief Benchmark using a fixture
 */
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "../units/stat_bench/param/create_ordinary_parameter_dict.h"
#include "stat_bench/bench/invocation_context.h"
#include "stat_bench/benchmark_macros.h"

static std::atomic<int> state{0};

class Fixture : public stat_bench::FixtureBase {
public:
    void setup(stat_bench::bench::InvocationContext& context) override {
        const std::size_t size = context.iterations();
        input_.resize(size);
        state = 1;
    }

    void tear_down(stat_bench::bench::InvocationContext& context) override {
        REQUIRE(state.load() == 2);
        state = 3;
    }

protected:
    //! Input vector.
    std::vector<double> input_{};
};

STAT_BENCH_CASE_F(Fixture, "Arithmetic", "Add") {
    REQUIRE(state.load() == 1);
    state = 2;

    STAT_BENCH_MEASURE_INDEXED(
        /*THREAD_INDEX_VAR*/, /*SAMPLE_INDEX_VAR*/, iteration_index) {
        ++input_[iteration_index];
    };
}

TEST_CASE("STAT_BENCH_CASE_F") {
    const auto& benchmarks =
        stat_bench::bench::BenchmarkCaseRegistry::instance().benchmarks();

    REQUIRE(benchmarks.size() == 1);
    REQUIRE(benchmarks.at(0).name() == "Arithmetic");
    REQUIRE(benchmarks.at(0).cases().size() == 1);
    REQUIRE(benchmarks.at(0).cases().at(0)->info().case_name() == "Add");

    stat_bench::bench::InvocationContext context{
        stat_bench::bench::BenchmarkCondition(
            1, stat_bench_test::param::create_ordinary_parameter_dict()),
        1, 1, 0};

    state = 1;
    REQUIRE_NOTHROW(benchmarks.at(0).cases().at(0)->execute(context));
    REQUIRE(state.load() == 3);
}
