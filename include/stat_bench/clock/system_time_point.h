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
 * \brief Definition of SystemTimePoint class.
 */
#pragma once

#include <chrono>

#include <fmt/chrono.h>
#include <fmt/format.h>

namespace stat_bench {
namespace clock {

/*!
 * \brief Class of time points of system clocks.
 */
class SystemTimePoint {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] time_point Actual time point.
     */
    explicit SystemTimePoint(
        std::chrono::system_clock::time_point time_point) noexcept
        : time_point_(time_point) {}

    /*!
     * \brief Get string expression.
     *
     * \return String expression.
     */
    [[nodiscard]] auto to_string() const -> std::string {
        const auto time_sec =
            std::chrono::time_point_cast<std::chrono::seconds>(time_point_);
        const auto time_tm =
            fmt::localtime(std::chrono::system_clock::to_time_t(time_sec));
        const auto time_usec =
            std::chrono::duration_cast<std::chrono::microseconds>(
                time_point_ - time_sec)
                .count();

        return fmt::format("{0:%FT%T}.{1:06d}{0:%z}", time_tm, time_usec);
    }

private:
    //! Actual time point.
    std::chrono::system_clock::time_point time_point_;
};

}  // namespace clock
}  // namespace stat_bench
