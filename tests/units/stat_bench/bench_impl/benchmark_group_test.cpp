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
 * \brief Test of BenchmarkGroup class.
 */
#include "stat_bench/bench_impl/benchmark_group.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <trompeloeil.hpp>

#include "../mock_benchmark_case.h"
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"

TEST_CASE("stat_bench::bench_impl::BenchmarkGroup") {
    using stat_bench::BenchmarkCaseName;
    using stat_bench::BenchmarkGroupName;

    SECTION("construct") {
        const auto group_name = BenchmarkGroupName("Group");

        const stat_bench::bench_impl::BenchmarkGroup group{group_name};

        CHECK(group.name() == group_name);
        CHECK_THAT(group.cases(), Catch::Matchers::IsEmpty());
    }

    SECTION("add cases") {
        const auto group_name = BenchmarkGroupName("Group");

        const auto case_name1 = BenchmarkCaseName("case1");
        const auto case_name2 = BenchmarkCaseName("case2");

        const auto info1 =
            stat_bench::BenchmarkFullName(group_name, case_name1);
        const auto info2 =
            stat_bench::BenchmarkFullName(group_name, case_name2);

        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        const auto case2 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        {
            ALLOW_CALL(*case1, info())
                // NOLINTNEXTLINE
                .RETURN(info1);
            ALLOW_CALL(*case2, info())
                // NOLINTNEXTLINE
                .RETURN(info2);

            stat_bench::bench_impl::BenchmarkGroup group{group_name};
            REQUIRE_NOTHROW(group.add(case2));
            REQUIRE_NOTHROW(group.add(case1));

            CHECK(group.cases().size() == 2);
            CHECK(group.cases().at(0)->info().case_name() == case_name2);
            CHECK(group.cases().at(1)->info().case_name() == case_name1);
        }
    }

    SECTION("duplicate case names") {
        const auto group_name = BenchmarkGroupName("Group");

        const auto case_name1 = BenchmarkCaseName("case1");
        const auto case_name2 = BenchmarkCaseName("case1");

        const auto info1 =
            stat_bench::BenchmarkFullName(group_name, case_name1);
        const auto info2 =
            stat_bench::BenchmarkFullName(group_name, case_name2);

        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        const auto case2 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        {
            ALLOW_CALL(*case1, info())
                // NOLINTNEXTLINE
                .RETURN(info1);
            ALLOW_CALL(*case2, info())
                // NOLINTNEXTLINE
                .RETURN(info2);

            stat_bench::bench_impl::BenchmarkGroup group{group_name};
            REQUIRE_NOTHROW(group.add(case2));
            REQUIRE_THROWS(group.add(case1));
        }
    }

    SECTION("wrong group name") {
        const auto group_name1 = BenchmarkGroupName("Group1");
        const auto group_name2 = BenchmarkGroupName("Group2");

        const auto case_name1 = BenchmarkCaseName("case1");

        const auto info1 =
            stat_bench::BenchmarkFullName(group_name1, case_name1);

        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        {
            ALLOW_CALL(*case1, info())
                // NOLINTNEXTLINE
                .RETURN(info1);

            stat_bench::bench_impl::BenchmarkGroup group{group_name2};
            REQUIRE_THROWS(group.add(case1));
        }
    }
}
