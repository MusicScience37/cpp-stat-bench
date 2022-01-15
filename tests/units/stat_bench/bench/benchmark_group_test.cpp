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
#include "stat_bench/bench/benchmark_group.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>

#include "mock_benchmark_case.h"

TEST_CASE("stat_bench::bench::BenchmarkGroup") {
    SECTION("construct") {
        const std::string group_name = "Group";

        const stat_bench::bench::BenchmarkGroup group{group_name};

        REQUIRE(group.name() == group_name);
        REQUIRE_THAT(group.cases(), Catch::Matchers::IsEmpty());
    }

    SECTION("add cases") {
        const std::string group_name = "Group";

        const std::string case_name1 = "case1";
        const std::string case_name2 = "case2";

        const auto info1 =
            stat_bench::bench::BenchmarkCaseInfo(group_name, case_name1);
        const auto info2 =
            stat_bench::bench::BenchmarkCaseInfo(group_name, case_name2);

        const auto case1 =
            std::make_shared<stat_bench_test::bench::MockBenchmarkCase>();
        const auto case2 =
            std::make_shared<stat_bench_test::bench::MockBenchmarkCase>();
        {
            ALLOW_CALL(*case1, info())
                // NOLINTNEXTLINE
                .RETURN(info1);
            ALLOW_CALL(*case2, info())
                // NOLINTNEXTLINE
                .RETURN(info2);

            stat_bench::bench::BenchmarkGroup group{group_name};
            group.add(case2);
            group.add(case1);

            REQUIRE(group.cases().size() == 2);
            REQUIRE(group.cases().at(0)->info().case_name() == case_name2);
            REQUIRE(group.cases().at(1)->info().case_name() == case_name1);
        }
    }
}
