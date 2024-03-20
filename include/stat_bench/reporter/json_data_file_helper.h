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
 * \brief Helper of JSON data files.
 */
#pragma once

#include <nlohmann/json.hpp>

#include "stat_bench/reporter/data_file_spec.h"

namespace stat_bench {
namespace reporter {
namespace data_file_spec {

#ifndef STAT_BENCH_DOCUMENTATION

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StatData, mean, max, min, median, variance,
    standard_deviation, standard_error)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DurationData, stat, values)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CustomStatOutputData, name, stat, values)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CustomOutputData, name, value)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MeasurementData, group_name, case_name,
    params, measurer_name, iterations, samples, durations, custom_stat_outputs,
    custom_outputs)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    RootData, started_at, finished_at, measurements)

#endif

}  // namespace data_file_spec
}  // namespace reporter
}  // namespace stat_bench
