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
 * \brief Test of FixtureBase class.
 */
#include "stat_bench/fixture_base.h"

// IWYU pragma: no_include  <stddef.h>

#include <cstddef>
#include <stdexcept>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>

#include "mock_fixture.h"
#include "param/create_ordinary_parameter_dict.h"
#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/bench_impl/invocation_context_registry.h"
#include "stat_bench/benchmark_condition.h"

TEST_CASE("stat_bench::FixtureBase") {
    stat_bench_test::MockFixture fixture;

    stat_bench::bench_impl::IBenchmarkCase& fixture_as_case = fixture;

    constexpr std::size_t threads = 1;
    constexpr std::size_t iterations = 7;
    constexpr std::size_t samples = 13;

    stat_bench::bench_impl::InvocationContextRegistry::instance().create(
        stat_bench::BenchmarkCondition(
            threads, stat_bench_test::param::create_ordinary_parameter_dict()),
        iterations, samples, 0);

    SECTION("execute") {
        trompeloeil::sequence seq;
        REQUIRE_CALL(fixture, setup(trompeloeil::_)).TIMES(1).IN_SEQUENCE(seq);
        REQUIRE_CALL(fixture, run()).TIMES(1).IN_SEQUENCE(seq);
        REQUIRE_CALL(fixture, tear_down(trompeloeil::_))
            .TIMES(1)
            .IN_SEQUENCE(seq);

        REQUIRE_NOTHROW(fixture_as_case.execute());
    }

    SECTION("execute to throw exception") {
        trompeloeil::sequence seq;
        REQUIRE_CALL(fixture, setup(trompeloeil::_)).TIMES(1).IN_SEQUENCE(seq);
        REQUIRE_CALL(fixture, run())
            .TIMES(1)
            .IN_SEQUENCE(seq)
            // NOLINTNEXTLINE
            .THROW(std::invalid_argument("Test exception"));
        REQUIRE_CALL(fixture, tear_down(trompeloeil::_))
            .TIMES(1)
            .IN_SEQUENCE(seq);

        REQUIRE_THROWS_AS(fixture_as_case.execute(), std::invalid_argument);
    }

    stat_bench::bench_impl::InvocationContextRegistry::instance().clear();
}
