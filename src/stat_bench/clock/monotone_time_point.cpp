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
 * \brief Implementation of classes of monotone clocks.
 */
#include "stat_bench/clock/monotone_time_point.h"

#include <chrono>

#include "stat_bench/clock/duration.h"

#if defined(STAT_BENCH_HAS_WIN_MONOTONE_CLOCK)

#include <cstdint>

// clang-format off
#include <windows.h>
#include <profileapi.h>
// clang-format on

namespace stat_bench {
namespace clock {

/*!
 * \brief Get the frequency of the monotone clock in Windows.
 *
 * \return Frequency.
 */
auto win_monotone_clock_frequency() noexcept -> std::int64_t {
    LARGE_INTEGER freq;
    // This never fails
    // (https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency).
    QueryPerformanceFrequency(&freq);
    return freq.QuadPart;
}

auto WinMonotoneTimePoint::operator-(
    const WinMonotoneTimePoint& right) const noexcept -> Duration {
    static const double resolution =
        1.0 / static_cast<double>(win_monotone_clock_frequency());
    return Duration(resolution * static_cast<double>(data_ - right.data_));
}

auto WinMonotoneTimePoint::now() noexcept -> WinMonotoneTimePoint {
    LARGE_INTEGER ticks;
    // This never fails
    // (https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter?redirectedfrom=MSDN).
    QueryPerformanceCounter(&ticks);
    return WinMonotoneTimePoint(ticks.QuadPart);
}

auto WinMonotoneTimePoint::resolution() noexcept -> Duration {
    static const double resolution =
        1.0 / static_cast<double>(win_monotone_clock_frequency());
    return Duration(resolution);
}

WinMonotoneTimePoint::WinMonotoneTimePoint(DataType data) noexcept
    : data_(data) {}

}  // namespace clock
}  // namespace stat_bench

#endif

#ifdef STAT_BENCH_HAS_UNIX_MONOTONE_CLOCK

#include <cstdio>
#include <cstdlib>

#include <time.h>  // NOLINT: std::timespec doesn't exist in C++ 14.

#ifdef CLOCK_MONOTONIC_RAW
#define STAT_BENCH_CLOCK_ID CLOCK_MONOTONIC_RAW
#else
#define STAT_BENCH_CLOCK_ID CLOCK_MONOTONIC
#endif

namespace stat_bench {
namespace clock {

auto UnixMonotoneTimePoint::operator-(
    const UnixMonotoneTimePoint& right) const noexcept -> Duration {
    constexpr double nsec_to_sec = 1e-9;
    return Duration(static_cast<double>(data_.tv_sec - right.data_.tv_sec) +
        nsec_to_sec * static_cast<double>(data_.tv_nsec - right.data_.tv_nsec));
}

auto UnixMonotoneTimePoint::now() noexcept -> UnixMonotoneTimePoint {
    timespec ts{};
    if (clock_gettime(STAT_BENCH_CLOCK_ID, &ts) != 0) {
        std::perror("Failed to get the current tick.");
        std::abort();
    }
    return UnixMonotoneTimePoint(ts);
}

auto UnixMonotoneTimePoint::resolution() noexcept -> Duration {
    timespec ts{};
    if (clock_getres(STAT_BENCH_CLOCK_ID, &ts) != 0) {
        std::perror("Failed to get the resolution of the clock.");
        std::abort();
    }
    constexpr double nsec_to_sec = 1e-9;
    return Duration(static_cast<double>(ts.tv_sec) +
        nsec_to_sec * static_cast<double>(ts.tv_nsec));
}

UnixMonotoneTimePoint::UnixMonotoneTimePoint(DataType data) noexcept
    : data_(data) {}

}  // namespace clock
}  // namespace stat_bench

#endif

namespace stat_bench {
namespace clock {

auto StdMonotoneTimePoint::operator-(
    const StdMonotoneTimePoint& right) const noexcept -> Duration {
    return Duration(std::chrono::duration_cast<std::chrono::duration<double>>(
        data_ - right.data_)
            .count());
}

auto StdMonotoneTimePoint::now() noexcept -> StdMonotoneTimePoint {
    return StdMonotoneTimePoint(std::chrono::steady_clock::now());
}

auto StdMonotoneTimePoint::resolution() noexcept -> Duration {
    // This may not be true.
    return Duration(
        static_cast<double>(std::chrono::steady_clock::duration::period::num) /
        static_cast<double>(std::chrono::steady_clock::duration::period::den));
}

StdMonotoneTimePoint::StdMonotoneTimePoint(DataType data) noexcept
    : data_(data) {}

}  // namespace clock
}  // namespace stat_bench
