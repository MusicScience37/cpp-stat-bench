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
 * \brief Definition of MockFixture class.
 */
#pragma once

#include "../trompeloeil.h"
#include "stat_bench/fixture_base.h"

namespace stat_bench_test {

class MockFixture final : public stat_bench::FixtureBase {
public:
    // NOLINTNEXTLINE
    MAKE_CONST_MOCK0(
        info, const stat_bench::BenchmarkFullName&(), noexcept override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(setup, void(stat_bench::InvocationContext&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(tear_down, void(stat_bench::InvocationContext&), override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(run, void(stat_bench::InvocationContext&), override);

    MockFixture() = default;
    MockFixture(const MockFixture&) = delete;
    MockFixture(MockFixture&&) = delete;
    auto operator=(const MockFixture&) -> MockFixture& = delete;
    auto operator=(MockFixture&&) -> MockFixture& = delete;
    ~MockFixture() override = default;
};

}  // namespace stat_bench_test
