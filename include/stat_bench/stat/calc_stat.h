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
 * \brief Declaration of calc_stat function.
 */
#pragma once

#include <cstddef>
#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/stat/statistics.h"

namespace stat_bench::stat {

/*!
 * \brief Calculate statistics.
 *
 * \param[in] durations Durations.
 * \param[in] iterations Number of iterations.
 * \return Statistics.
 */
[[nodiscard]] auto calc_stat(
    const std::vector<std::vector<clock::Duration>>& durations,
    std::size_t iterations) -> stat::Statistics;

/*!
 * \brief Calculate statistics.
 *
 * \param[in] values Sample values.
 * \return Statistics.
 */
[[nodiscard]] auto calc_stat(const std::vector<std::vector<double>>& values)
    -> stat::Statistics;

}  // namespace stat_bench::stat
