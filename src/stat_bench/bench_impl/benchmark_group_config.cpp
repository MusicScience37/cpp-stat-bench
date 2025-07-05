/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of BenchmarkGroupConfig class.
 */
#include "stat_bench/bench_impl/benchmark_group_config.h"

#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace bench_impl {
void BenchmarkGroupConfig::add_measurement_config(
    const MeasurementConfig& config) {
    const auto [iterator, added] =
        measurement_configs_.try_emplace(config.type(), config);
    if (!added) {
        throw StatBenchException("Duplicate measurement type \"" +
            config.type().str().str() + "\" in a group");
    }
}

}  // namespace bench_impl
}  // namespace stat_bench
