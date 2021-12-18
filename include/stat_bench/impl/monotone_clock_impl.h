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

#include "stat_bench/impl/stat_bench_export.h"

namespace stat_bench {
namespace impl {

/*!
 * \brief Get the current time using a monotone clock.
 *
 * \return Current time.
 */
[[nodiscard]] STAT_BENCH_EXPORT auto monotone_clock_now() noexcept
    -> std::uint64_t;

/*!
 * \brief Get the frequency using a monotone clock.
 *
 * \return Frequency.
 */
[[nodiscard]] STAT_BENCH_EXPORT auto monotone_clock_freq() noexcept
    -> std::uint64_t;

}  // namespace impl
}  // namespace stat_bench
