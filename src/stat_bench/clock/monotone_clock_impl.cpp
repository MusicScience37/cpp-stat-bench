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

#if defined(_WIN32)

/* *****************************************************************
 * For Windows.
 * *****************************************************************/

// clang-format off
#include <windows.h>
#include <profileapi.h>
#include <iostream>
// clang-format on

namespace stat_bench {
namespace clock {
namespace impl {

auto monotone_clock_now() noexcept -> TicksCount {
    LARGE_INTEGER ticks;
    // This never fails
    // (https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter?redirectedfrom=MSDN).
    QueryPerformanceCounter(&ticks);
    return ticks.QuadPart;
}

/*!
 * \brief Get the frequency of ticks in a monotone clock.
 *
 * \return Frequency.
 */
static auto monotone_clock_freq_impl() noexcept -> TicksCount {
    LARGE_INTEGER freq;
    // This never fails
    // (https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency).
    QueryPerformanceFrequency(&freq);
    return freq.QuadPart;
}

auto monotone_clock_freq() noexcept -> TicksCount {
    static TicksCount freq = monotone_clock_freq_impl();
    return freq;
}

auto monotone_clock_res() noexcept -> TicksCount { return 1; }

}  // namespace impl
}  // namespace clock
}  // namespace stat_bench

#elif defined(__unix__)

/* *****************************************************************
 * For UNIX.
 * *****************************************************************/

#include <cstdio>
#include <cstdlib>

#include <time.h>  // NOLINT

#ifdef CLOCK_MONOTONIC_RAW
#define STAT_BENCH_CLOCK_ID CLOCK_MONOTONIC_RAW
#else
#define STAT_BENCH_CLOCK_ID CLOCK_MONOTONIC
#endif

namespace stat_bench {
namespace clock {
namespace impl {

static constexpr TicksCount freq = 1000000000;

auto monotone_clock_now() noexcept -> TicksCount {
    timespec ts{};
    if (clock_gettime(STAT_BENCH_CLOCK_ID, &ts) != 0) {
        std::perror("Failed to get the current tick.");
        std::abort();
    }
    auto ticks = static_cast<TicksCount>(ts.tv_sec);
    ticks *= freq;
    ticks += ts.tv_nsec;
    return ticks;
}

auto monotone_clock_freq() noexcept -> TicksCount { return freq; }

auto monotone_clock_res() noexcept -> TicksCount {
    timespec ts{};
    if (clock_getres(STAT_BENCH_CLOCK_ID, &ts) != 0) {
        std::perror("Failed to get the resolution of the clock.");
        std::abort();
    }
    auto ticks = static_cast<TicksCount>(ts.tv_sec);
    ticks *= freq;
    ticks += ts.tv_nsec;
    return ticks;
}

}  // namespace impl
}  // namespace clock
}  // namespace stat_bench

#else

/* *****************************************************************
 * Fallback using C++ standard library.
 * *****************************************************************/

#include <chrono>

namespace stat_bench {
namespace clock {
namespace impl {

auto monotone_clock_now() noexcept -> TicksCount {
    return static_cast<TicksCount>(
        std::chrono::steady_clock::now().time_since_epoch().count());
}

auto monotone_clock_freq() noexcept -> TicksCount {
    static const auto freq = static_cast<TicksCount>(
        std::chrono::steady_clock::duration::period::den /
        std::chrono::steady_clock::duration::period::num);
    return freq;
}

auto monotone_clock_res() noexcept -> TicksCount { return 1; }

}  // namespace impl
}  // namespace clock
}  // namespace stat_bench

#endif
