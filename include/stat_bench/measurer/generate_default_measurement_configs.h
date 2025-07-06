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
 * \brief Definition of generate_default_measurement_configs function.
 */
#pragma once

#include "stat_bench/measurement_config.h"
#include "stat_bench/measurer/measurement_type.h"
#include "stat_bench/util/ordered_map.h"

namespace stat_bench {
namespace measurer {

/*!
 * \brief Generate default measurement configurations.
 *
 * \return Measurement configurations.
 */
auto generate_default_measurement_configs()
    -> util::OrderedMap<MeasurementType, MeasurementConfig>;

}  // namespace measurer
}  // namespace stat_bench
