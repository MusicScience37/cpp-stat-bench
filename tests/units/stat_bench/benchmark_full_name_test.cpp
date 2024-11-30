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
 * \brief Definition of BenchmarkFullName class.
 */
#include "stat_bench/benchmark_full_name.h"

#include <string>

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_group_name.h"

TEST_CASE("stat_bench::BenchmarkFullName") {
    SECTION("construct") {
        const auto group_name = stat_bench::BenchmarkGroupName("group");
        const auto case_name = stat_bench::BenchmarkCaseName("case");

        const auto info = stat_bench::BenchmarkFullName(group_name, case_name);

        REQUIRE(info.group_name() == group_name);
        REQUIRE(info.case_name() == case_name);
    }

    SECTION("format") {
        const auto group_name = stat_bench::BenchmarkGroupName("group");
        const auto case_name = stat_bench::BenchmarkCaseName("case");

        const auto info = stat_bench::BenchmarkFullName(group_name, case_name);

        REQUIRE(fmt::format("{}", info) == "group/case");
    }
}
