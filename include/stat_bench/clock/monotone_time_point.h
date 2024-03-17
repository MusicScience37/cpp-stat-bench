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
 * \brief Definition of MonotoneTimePoint class.
 */
#pragma once

#include <cstdint>

#include "stat_bench/clock/duration.h"

namespace stat_bench {
namespace clock {

/*!
 * \brief Class of time points of the monotone clock.
 */
class MonotoneTimePoint {
public:
    //! Data type.
    using DataType = std::int64_t;

    /*!
     * \brief Calculate a duration between two time points.
     *
     * \param[in] right Right-hand-side object.
     * \return Duration.
     */
    [[nodiscard]] auto operator-(const MonotoneTimePoint& right) const noexcept
        -> Duration;

    /*!
     * \brief Get the current time from the monotone clock.
     *
     * \return Time point.
     */
    [[nodiscard]] static auto now() noexcept -> MonotoneTimePoint;

    /*!
     * \brief Get the resolution of the monotone clock.
     *
     * \return Resolution.
     */
    [[nodiscard]] static auto resolution() noexcept -> Duration;

private:
    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     */
    explicit MonotoneTimePoint(DataType data) noexcept;

    //! Data.
    DataType data_;
};

}  // namespace clock
}  // namespace stat_bench
