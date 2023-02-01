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
 * \brief Definition of Duration class.
 */
#pragma once

#include "stat_bench/clock/monotone_clock_impl.h"

namespace stat_bench {
namespace clock {

/*!
 * \brief Class of durations.
 */
class Duration {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] count Number of ticks.
     */
    explicit Duration(TicksCount count) noexcept : count_(count) {}

    /*!
     * \brief Get the number of ticks.
     *
     * \return Number of ticks.
     */
    [[nodiscard]] auto count() const noexcept -> TicksCount { return count_; }

    /*!
     * \brief Get the frequency of ticks.
     *
     * \return Frequency of ticks.
     */
    [[nodiscard]] static auto freq() noexcept -> TicksCount {
        return impl::monotone_clock_freq();
    }

    /*!
     * \brief Get as seconds.
     *
     * \return Seconds.
     */
    [[nodiscard]] auto seconds() const noexcept -> double {
        return static_cast<double>(count()) / static_cast<double>(freq());
    }

private:
    //! Number of ticks.
    TicksCount count_;
};

}  // namespace clock
}  // namespace stat_bench
