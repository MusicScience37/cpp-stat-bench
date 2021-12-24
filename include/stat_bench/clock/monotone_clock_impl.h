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
 * \brief Declration of functions for monotone clocks.
 */
#pragma once

#include <cstdint>

namespace stat_bench {
namespace clock {

/*!
 * \brief Type of numbers of ticks.
 */
using TicksCount = std::int64_t;

namespace impl {

/*!
 * \brief Get the current time using a monotone clock.
 *
 * \return Current time.
 */
[[nodiscard]] auto monotone_clock_now() noexcept -> TicksCount;

/*!
 * \brief Get the frequency of ticks in a monotone clock.
 *
 * \return Frequency.
 */
[[nodiscard]] auto monotone_clock_freq() noexcept -> TicksCount;

/*!
 * \brief Get the resolution of ticks in a monotone clock.
 *
 * \return Resolution.
 */
[[nodiscard]] auto monotone_clock_res() noexcept -> TicksCount;

}  // namespace impl
}  // namespace clock
}  // namespace stat_bench
