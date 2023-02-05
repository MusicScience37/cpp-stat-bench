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
 * \brief Definition of create_test_measurement function.
 */
#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/stat/custom_stat_output.h"

namespace stat_bench_test {

[[nodiscard]] inline auto create_test_measurement(const std::string& group_name,
    const std::string& case_name, const std::string& measurer_name,
    const std::vector<std::vector<stat_bench::clock::Duration>>& durations) {
    using stat_bench::BenchmarkCondition;
    using stat_bench::BenchmarkFullName;
    using stat_bench::clock::Duration;
    using stat_bench::measurer::Measurement;
    using stat_bench::param::ParameterDict;
    using stat_bench::param::ParameterValue;
    using stat_bench::stat::CustomStatOutput;

    constexpr std::size_t iterations = 1000;
    const std::size_t samples = durations.front().size();
    const std::size_t threads = durations.size();
    return Measurement(BenchmarkFullName(group_name, case_name),
        BenchmarkCondition(
            ParameterDict(std::unordered_map<std::string, ParameterValue>{
                {"threads", ParameterValue().emplace<std::size_t>(threads)},
                {"param", ParameterValue().emplace<std::string>("value")}})),
        measurer_name, iterations, samples, durations,
        std::vector<std::shared_ptr<CustomStatOutput>>(),
        std::vector<std::pair<std::string, double>>());
}

}  // namespace stat_bench_test
