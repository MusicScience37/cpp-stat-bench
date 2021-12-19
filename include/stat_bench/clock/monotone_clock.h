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
 * \brief Definition of MonotoneClock class.
 */
#pragma once

#include "stat_bench/clock/monotone_clock_impl.h"
#include "stat_bench/clock/monotone_time_point.h"

namespace stat_bench {
namespace clock {

/*!
 * \brief Class of a monotone clock.
 */
class MonotoneClock {
public:
    /*!
     * \brief Get the current time.
     *
     * \return Time point.
     */
    [[nodiscard]] static auto now() noexcept -> MonotoneTimePoint {
        return MonotoneTimePoint(impl::monotone_clock_now());
    }
};

}  // namespace clock
}  // namespace stat_bench
