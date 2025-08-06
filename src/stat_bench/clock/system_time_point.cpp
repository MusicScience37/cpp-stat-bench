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
 * \brief Implementation of SystemTimePoint class.
 */
#include "stat_bench/clock/system_time_point.h"

#include <fmt/chrono.h>
#include <fmt/format.h>

namespace fmt {

auto formatter<stat_bench::clock::SystemTimePoint>::format(
    const stat_bench::clock::SystemTimePoint& val,
    format_context& context) const -> format_context::iterator {
    const auto time_point = val.time_point();
    const auto time_sec =
        std::chrono::time_point_cast<std::chrono::seconds>(time_point);
    const auto time_usec =
        std::chrono::duration_cast<std::chrono::microseconds>(
            time_point - time_sec)
            .count();

    return fmt::format_to(
        context.out(), "{0:%FT%T}.{1:06d}{0:%z}", time_sec, time_usec);
}

}  // namespace fmt
