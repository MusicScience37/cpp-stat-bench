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
 * \brief Test of ComposedFilter class.
 */
#include "stat_bench/filters/composed_filter.h"

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/benchmark_full_name.h"

TEST_CASE("stat_bench::filters::ComposedFilter") {
    using stat_bench::BenchmarkFullName;
    using stat_bench::filters::ComposedFilter;

    SECTION("empty filter") {
        ComposedFilter filter;
        CHECK(filter.check(BenchmarkFullName("abc", "def")));
        CHECK(filter.check(BenchmarkFullName("abc", "ghi")));
        CHECK(filter.check(BenchmarkFullName("jkl", "ghi")));
    }

    SECTION("include_with_regex") {
        ComposedFilter filter;
        filter.include_with_regex("[a-z]+/ghi");
        CHECK_FALSE(filter.check(BenchmarkFullName("abc", "def")));
        CHECK(filter.check(BenchmarkFullName("abc", "ghi")));
        CHECK(filter.check(BenchmarkFullName("jkl", "ghi")));

        filter.include_with_regex("abc/[a-z]+");
        CHECK(filter.check(BenchmarkFullName("abc", "def")));
        CHECK(filter.check(BenchmarkFullName("abc", "ghi")));
        CHECK(filter.check(BenchmarkFullName("jkl", "ghi")));
    }

    SECTION("exclude_with_regex") {
        ComposedFilter filter;
        filter.exclude_with_regex("jkl/[a-z]+");
        CHECK(filter.check(BenchmarkFullName("abc", "def")));
        CHECK(filter.check(BenchmarkFullName("abc", "ghi")));
        CHECK_FALSE(filter.check(BenchmarkFullName("jkl", "ghi")));

        filter.exclude_with_regex("abc/ghi");
        CHECK(filter.check(BenchmarkFullName("abc", "def")));
        CHECK_FALSE(filter.check(BenchmarkFullName("abc", "ghi")));
        CHECK_FALSE(filter.check(BenchmarkFullName("jkl", "ghi")));
    }

    SECTION("composed filter") {
        ComposedFilter filter;
        filter.include_with_regex("[a-z]+/ghi");
        filter.exclude_with_regex("jkl/[a-z]+");
        CHECK_FALSE(filter.check(BenchmarkFullName("abc", "def")));
        CHECK(filter.check(BenchmarkFullName("abc", "ghi")));
        CHECK_FALSE(filter.check(BenchmarkFullName("jkl", "ghi")));
    }
}
