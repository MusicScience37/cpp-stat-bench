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
 * \brief Test of BenchmarkCaseRegistry class.
 */
#include "stat_bench/bench/benchmark_case_registry.h"

#include <type_traits>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <trompeloeil.hpp>

#include "mock_benchmark_case.h"

TEST_CASE("stat_bench::bench::BenchmarkCaseRegistry") {
    SECTION("construct") {
        stat_bench::bench::BenchmarkCaseRegistry registry;

        REQUIRE_THAT(registry.benchmarks(), Catch::Matchers::IsEmpty());
    }

    SECTION("add cases") {
        const std::string group_name1 = "Group1";
        const std::string group_name2 = "Group2";
        const std::string group_name3 = "Group2";

        const std::string case_name1 = "case1";
        const std::string case_name2 = "case2";
        const std::string case_name3 = "case3";

        const auto info1 =
            stat_bench::bench::BenchmarkFullName(group_name1, case_name1);
        const auto info2 =
            stat_bench::bench::BenchmarkFullName(group_name2, case_name2);
        const auto info3 =
            stat_bench::bench::BenchmarkFullName(group_name3, case_name3);

        const auto case1 =
            std::make_shared<stat_bench_test::bench::MockBenchmarkCase>();
        const auto case2 =
            std::make_shared<stat_bench_test::bench::MockBenchmarkCase>();
        const auto case3 =
            std::make_shared<stat_bench_test::bench::MockBenchmarkCase>();
        {
            ALLOW_CALL(*case1, info())
                // NOLINTNEXTLINE
                .RETURN(info1);
            ALLOW_CALL(*case2, info())
                // NOLINTNEXTLINE
                .RETURN(info2);
            ALLOW_CALL(*case3, info())
                // NOLINTNEXTLINE
                .RETURN(info3);

            stat_bench::bench::BenchmarkCaseRegistry registry;
            registry.add(case2);
            registry.add(case1);
            registry.add(case3);

            REQUIRE(registry.benchmarks().size() == 2);

            const auto& group1 = registry.benchmarks().at(0);
            REQUIRE(group1.name() == group_name1);
            REQUIRE(group1.cases().size() == 1);
            REQUIRE(group1.cases().at(0)->info().group_name() == group_name1);
            REQUIRE(group1.cases().at(0)->info().case_name() == case_name1);

            const auto& group2 = registry.benchmarks().at(1);
            REQUIRE(group2.name() == group_name2);
            REQUIRE(group2.cases().size() == 2);
            REQUIRE(group2.cases().at(0)->info().group_name() == group_name2);
            REQUIRE(group2.cases().at(0)->info().case_name() == case_name2);
            REQUIRE(group2.cases().at(1)->info().group_name() == group_name3);
            REQUIRE(group2.cases().at(1)->info().case_name() == case_name3);
        }
    }
}
