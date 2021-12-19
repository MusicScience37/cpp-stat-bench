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
 * \brief Definition of functions for monotone clocks.
 */
#include "stat_bench/clock/monotone_clock_impl.h"

#include <chrono>

namespace stat_bench {
namespace clock {
namespace impl {

auto monotone_clock_now() noexcept -> TicksCount {
    return static_cast<TicksCount>(
        std::chrono::steady_clock::now().time_since_epoch().count());
}

auto monotone_clock_freq() noexcept -> TicksCount {
    return static_cast<TicksCount>(
        std::chrono::steady_clock::duration::period::den /
        std::chrono::steady_clock::duration::period::num);
}

}  // namespace impl
}  // namespace clock
}  // namespace stat_bench
