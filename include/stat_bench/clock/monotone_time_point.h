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
 * \brief Definition of classes of monotone clocks.
 */
#pragma once

#include <chrono>

#include "stat_bench/clock/duration.h"

#if defined(STAT_BENCH_DOCUMENTATION)
#include <cstdint>
#include <ctime>
#elif defined(_WIN32)
#define STAT_BENCH_HAS_WIN_MONOTONE_CLOCK 1
#include <cstdint>
#elif defined(__unix__)
#define STAT_BENCH_HAS_UNIX_MONOTONE_CLOCK 1
#include <ctime>
#else
// No definition here.
#endif

namespace stat_bench::clock {

#if defined(STAT_BENCH_DOCUMENTATION) || \
    defined(STAT_BENCH_HAS_WIN_MONOTONE_CLOCK)

/*!
 * \brief Class of time points of the monotone clock in Windows.
 *
 * \note This class is defined only in Windows.
 */
class WinMonotoneTimePoint {
public:
    /*!
     * \brief Calculate a duration between two time points.
     *
     * \param[in] right Right-hand-side object.
     * \return Duration.
     */
    [[nodiscard]] auto operator-(
        const WinMonotoneTimePoint& right) const noexcept -> Duration;

    /*!
     * \brief Get the current time from the monotone clock.
     *
     * \return Time point.
     */
    [[nodiscard]] static auto now() noexcept -> WinMonotoneTimePoint;

    /*!
     * \brief Get the resolution of the monotone clock.
     *
     * \return Resolution.
     */
    [[nodiscard]] static auto resolution() noexcept -> Duration;

private:
    //! Data type.
    using DataType = std::int64_t;

    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     */
    explicit WinMonotoneTimePoint(DataType data) noexcept;

    //! Data.
    DataType data_;
};

#endif

#if defined(STAT_BENCH_DOCUMENTATION) || \
    defined(STAT_BENCH_HAS_UNIX_MONOTONE_CLOCK)

/*!
 * \brief Class of time points of the monotone clock in Unix.
 *
 * \note This class is defined only in Unix.
 */
class UnixMonotoneTimePoint {
public:
    /*!
     * \brief Calculate a duration between two time points.
     *
     * \param[in] right Right-hand-side object.
     * \return Duration.
     */
    [[nodiscard]] auto operator-(
        const UnixMonotoneTimePoint& right) const noexcept -> Duration;

    /*!
     * \brief Get the current time from the monotone clock.
     *
     * \return Time point.
     */
    [[nodiscard]] static auto now() noexcept -> UnixMonotoneTimePoint;

    /*!
     * \brief Get the resolution of the monotone clock.
     *
     * \return Resolution.
     */
    [[nodiscard]] static auto resolution() noexcept -> Duration;

private:
    //! Data type.
    using DataType = std::timespec;

    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     */
    explicit UnixMonotoneTimePoint(DataType data) noexcept;

    //! Data.
    DataType data_;
};

#endif

/*!
 * \brief Class of time points of the monotone clock in C++ standard library.
 *
 * \note This class is defined for fallback for environments which is not
 * Windows of Unix.
 */
class StdMonotoneTimePoint {
public:
    /*!
     * \brief Calculate a duration between two time points.
     *
     * \param[in] right Right-hand-side object.
     * \return Duration.
     */
    [[nodiscard]] auto operator-(
        const StdMonotoneTimePoint& right) const noexcept -> Duration;

    /*!
     * \brief Get the current time from the monotone clock.
     *
     * \return Time point.
     */
    [[nodiscard]] static auto now() noexcept -> StdMonotoneTimePoint;

    /*!
     * \brief Get the resolution of the monotone clock.
     *
     * \return Resolution.
     */
    [[nodiscard]] static auto resolution() noexcept -> Duration;

private:
    //! Data type.
    using DataType = std::chrono::steady_clock::time_point;

    /*!
     * \brief Constructor.
     *
     * \param[in] data Data.
     */
    explicit StdMonotoneTimePoint(DataType data) noexcept;

    //! Data.
    DataType data_;
};

#if defined(STAT_BENCH_DOCUMENTATION)
//! Type of the monotone clock to use.
using MonotoneTimePoint = <platform_dependent_type>;
#elif defined(STAT_BENCH_HAS_WIN_MONOTONE_CLOCK)
// Monotone clock in Windows.
using MonotoneTimePoint = WinMonotoneTimePoint;
#elif defined(STAT_BENCH_HAS_UNIX_MONOTONE_CLOCK)
// Monotone clock in Unix.
using MonotoneTimePoint = UnixMonotoneTimePoint;
#else
// Fallback using C++ standard library.
using MonotoneTimePoint = StdMonotoneTimePoint;
#endif

}  // namespace stat_bench::clock
