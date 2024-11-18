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
#include "stat_bench/bench_impl/benchmark_case_registry.h"

#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <trompeloeil.hpp>

#include "../mock_benchmark_case.h"
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/filters/composed_filter.h"

TEST_CASE("stat_bench::bench_impl::BenchmarkCaseRegistry") {
    using stat_bench::BenchmarkCaseName;
    using stat_bench::BenchmarkFullName;
    using stat_bench::BenchmarkGroupName;

    SECTION("construct") {
        stat_bench::bench_impl::BenchmarkCaseRegistry registry;

        REQUIRE_THAT(registry.benchmarks(), Catch::Matchers::IsEmpty());
    }

    SECTION("add cases") {
        const auto group_name1 = BenchmarkGroupName("Group1");
        const auto group_name2 = BenchmarkGroupName("Group2");
        const auto group_name3 = BenchmarkGroupName("Group2");

        const auto case_name1 = BenchmarkCaseName("case1");
        const auto case_name2 = BenchmarkCaseName("case2");
        const auto case_name3 = BenchmarkCaseName("case3");

        const auto info1 =
            stat_bench::BenchmarkFullName(group_name1, case_name1);
        const auto info2 =
            stat_bench::BenchmarkFullName(group_name2, case_name2);
        const auto info3 =
            stat_bench::BenchmarkFullName(group_name3, case_name3);

        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        const auto case2 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        const auto case3 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
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

            stat_bench::bench_impl::BenchmarkCaseRegistry registry;
            registry.add(case1);
            registry.add(case2);
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

    SECTION("filter cases") {
        const auto group_name1 = BenchmarkGroupName("Group1");
        const auto group_name2 = BenchmarkGroupName("Group2");
        const auto group_name3 = BenchmarkGroupName("Group2");

        const auto case_name1 = BenchmarkCaseName("case1");
        const auto case_name2 = BenchmarkCaseName("case2");
        const auto case_name3 = BenchmarkCaseName("case3");

        const auto info1 =
            stat_bench::BenchmarkFullName(group_name1, case_name1);
        const auto info2 =
            stat_bench::BenchmarkFullName(group_name2, case_name2);
        const auto info3 =
            stat_bench::BenchmarkFullName(group_name3, case_name3);

        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        const auto case2 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        const auto case3 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();

        stat_bench::filters::ComposedFilter filter;
        filter.include_with_regex(group_name1.str().str() + "/.*");

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

            stat_bench::bench_impl::BenchmarkCaseRegistry registry;
            registry.add(case1);
            registry.add(case2);
            registry.add(case3);

            REQUIRE(registry.benchmarks().size() == 2);

            const auto& group1 = registry.benchmarks().at(0);
            REQUIRE(group1.name() == group_name1);
            REQUIRE(group1.cases().size() == 1);
            REQUIRE(group1.cases().at(0)->info().group_name() == group_name1);
            REQUIRE(group1.cases().at(0)->info().case_name() == case_name1);
        }
    }
}
