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
 * \brief Test of RegexFilter class.
 */
#include "stat_bench/filters/regex_filter.h"

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/bench/benchmark_case_info.h"
#include "stat_bench/filters/i_name_filter.h"

TEST_CASE("stat_bench::filters::RegexFilter") {
    using stat_bench::bench::BenchmarkCaseInfo;
    using stat_bench::filters::INameFilter;
    using stat_bench::filters::RegexFilter;

    SECTION("check") {
        std::shared_ptr<INameFilter> filter =
            std::make_shared<RegexFilter>("a[bc]+/.*");

        CHECK(filter->check(BenchmarkCaseInfo("abc", "def")));
        CHECK_FALSE(filter->check(BenchmarkCaseInfo("a", "abc")));
    }
}
