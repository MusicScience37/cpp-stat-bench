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
 * \brief Test of custom measurement.
 */
#include <chrono>
#include <string>
#include <thread>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/measurement_config.h"

static constexpr auto duration = std::chrono::milliseconds(10);

STAT_BENCH_CASE("Group1", "Case1") {
    STAT_BENCH_MEASURE() { std::this_thread::sleep_for(duration); };
}

STAT_BENCH_GROUP("Group1").clear_measurement_configs().add_measurement_config(
    stat_bench::MeasurementConfig()
        .type("Custom Measurement")
        .samples(2)
        .iterations(3)
        .warming_up_samples(0));

STAT_BENCH_MAIN
