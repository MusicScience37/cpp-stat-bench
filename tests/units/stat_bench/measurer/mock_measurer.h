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
 * \brief Definition of MockMeasurer class.
 */
#pragma once

#include "../../trompeloeil.h"
#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/measurer/i_measurer.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurement_type.h"

namespace stat_bench_test::measurer {

class MockMeasurer final : public stat_bench::measurer::IMeasurer {
public:
    // NOLINTNEXTLINE
    MAKE_CONST_MOCK0(type, const stat_bench::measurer::MeasurementType&(),
        noexcept override);

    // NOLINTNEXTLINE
    MAKE_CONST_MOCK2(measure,
        stat_bench::measurer::Measurement(
            stat_bench::bench_impl::IBenchmarkCase*,
            const stat_bench::BenchmarkCondition&),
        override);

    MockMeasurer() = default;
    MockMeasurer(const MockMeasurer&) = delete;
    MockMeasurer(MockMeasurer&&) = delete;
    auto operator=(const MockMeasurer&) -> MockMeasurer& = delete;
    auto operator=(MockMeasurer&&) -> MockMeasurer& = delete;
    ~MockMeasurer() override = default;
};

}  // namespace stat_bench_test::measurer
