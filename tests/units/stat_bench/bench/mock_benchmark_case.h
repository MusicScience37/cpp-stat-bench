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
 * \brief Definition of MockBenchmarkCase class.
 */
#pragma once

#include "../../trompeloeil.h"
#include "stat_bench/bench/i_benchmark_case.h"

namespace stat_bench_test {
namespace bench {

class MockBenchmarkCase final : public stat_bench::bench::IBenchmarkCase {
public:
    // NOLINTNEXTLINE
    MAKE_CONST_MOCK0(
        info, const stat_bench::bench::BenchmarkCaseInfo&(), noexcept override);

    // NOLINTNEXTLINE
    MAKE_MOCK1(execute, void(stat_bench::bench::InvocationContext&), override);

    MockBenchmarkCase() = default;
    MockBenchmarkCase(const MockBenchmarkCase&) = delete;
    MockBenchmarkCase(MockBenchmarkCase&&) = delete;
    auto operator=(const MockBenchmarkCase&) -> MockBenchmarkCase& = delete;
    auto operator=(MockBenchmarkCase&&) -> MockBenchmarkCase& = delete;
    ~MockBenchmarkCase() override = default;
};

}  // namespace bench
}  // namespace stat_bench_test
