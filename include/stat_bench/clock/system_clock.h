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
 * \brief Definition of SystemClock class.
 */
#pragma once

#include <chrono>

#include "stat_bench/clock/system_time_point.h"

namespace stat_bench {
namespace clock {

/*!
 * \brief Class of a system clock.
 */
class SystemClock {
public:
    /*!
     * \brief Get the current time.
     *
     * \return Current time.
     */
    [[nodiscard]] static auto now() -> SystemTimePoint {
        return SystemTimePoint(std::chrono::system_clock::now());
    }
};

}  // namespace clock
}  // namespace stat_bench
