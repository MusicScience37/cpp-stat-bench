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
 * \brief Test of BenchmarkCondition class.
 */
#include "stat_bench/benchmark_condition.h"

#include <string>
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "param/create_ordinary_parameter_dict.h"

TEST_CASE("stat_bench::BenchmarkCondition") {
    SECTION("construct") {
        constexpr std::size_t threads = 7;

        const auto cond = stat_bench::BenchmarkCondition(
            threads, stat_bench_test::param::create_ordinary_parameter_dict());

        REQUIRE(cond.threads() == threads);
        REQUIRE(fmt::format("{}", cond.params()) == "threads=1");
    }
}
