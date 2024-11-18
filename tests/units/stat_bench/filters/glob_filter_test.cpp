/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of GlobFilter class.
 */
#include "stat_bench/filters/glob_filter.h"

#include <memory>

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/filters/i_name_filter.h"

TEST_CASE("stat_bench::filters::GlobFilter") {
    using stat_bench::BenchmarkCaseName;
    using stat_bench::BenchmarkFullName;
    using stat_bench::BenchmarkGroupName;
    using stat_bench::filters::GlobFilter;
    using stat_bench::filters::INameFilter;

    SECTION("check") {
        const std::shared_ptr<INameFilter> filter =
            std::make_shared<GlobFilter>("*/test");

        CHECK(filter->check(BenchmarkFullName(
            BenchmarkGroupName("any"), BenchmarkCaseName("test"))));
        CHECK_FALSE(filter->check(BenchmarkFullName(
            BenchmarkGroupName("any"), BenchmarkCaseName("1test"))));
    }
}
