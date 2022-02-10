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
 * \brief Test of macros to define and register cases.
 */
#include <memory>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "../units/stat_bench/param/create_ordinary_parameter_dict.h"
#include "stat_bench/bench/benchmark_case_info.h"
#include "stat_bench/bench/benchmark_case_registry.h"
#include "stat_bench/bench/benchmark_condition.h"
#include "stat_bench/bench/benchmark_group.h"
#include "stat_bench/bench/i_benchmark_case.h"
#include "stat_bench/bench/invocation_context.h"
#include "stat_bench/benchmark_macros.h"

static auto case_index() -> int& {
    static int index = 0;
    return index;
}

STAT_BENCH_CASE("Group1", "Case1") {
    STAT_BENCH_MEASURE() { case_index() = 1; };
}

STAT_BENCH_CASE("Group1", "Case2") {
    STAT_BENCH_MEASURE() { case_index() = 2; };
}

STAT_BENCH_CASE("Group2", "Case3") {
    STAT_BENCH_MEASURE_INDEXED(thread_ind, sample_ind, iteration_ind) {
        CHECK(thread_ind == 0);
        CHECK(sample_ind == 0);
        CHECK(iteration_ind == 0);
        case_index() = 3;
    };
}

TEST_CASE("STAT_BENCH_CASE") {
    const auto& benchmarks =
        stat_bench::bench::BenchmarkCaseRegistry::instance().benchmarks();

    REQUIRE(benchmarks.size() == 2);
    REQUIRE(benchmarks.at(0).name() == "Group1");
    REQUIRE(benchmarks.at(1).name() == "Group2");
    REQUIRE(benchmarks.at(0).cases().size() == 2);
    REQUIRE(benchmarks.at(1).cases().size() == 1);

    stat_bench::bench::InvocationContext context{
        stat_bench::bench::BenchmarkCondition(
            1, stat_bench_test::param::create_ordinary_parameter_dict()),
        1, 1, 0};

    const auto& case1 = benchmarks.at(0).cases().at(0);
    REQUIRE(case1->info().group_name() == "Group1");
    REQUIRE(case1->info().case_name() == "Case1");
    REQUIRE_NOTHROW(case1->execute(context));
    REQUIRE(case_index() == 1);

    const auto& case2 = benchmarks.at(0).cases().at(1);
    REQUIRE(case2->info().group_name() == "Group1");
    REQUIRE(case2->info().case_name() == "Case2");
    REQUIRE_NOTHROW(case2->execute(context));
    REQUIRE(case_index() == 2);

    const auto& case3 = benchmarks.at(1).cases().at(0);
    REQUIRE(case3->info().group_name() == "Group2");
    REQUIRE(case3->info().case_name() == "Case3");
    REQUIRE_NOTHROW(case3->execute(context));
    REQUIRE(case_index() == 3);
}
