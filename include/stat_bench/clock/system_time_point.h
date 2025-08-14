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

#include <fmt/base.h>

namespace stat_bench::clock {

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
     * \brief Get the actual time point.
     *
     * \return Actual time point.
     */
    [[nodiscard]] auto time_point() const noexcept
        -> std::chrono::system_clock::time_point {
        return time_point_;
    }

private:
    //! Actual time point.
    std::chrono::system_clock::time_point time_point_;
};

}  // namespace stat_bench::clock

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for
 * stat_bench::clock::SystemTimePoint.
 */
template <>
struct formatter<stat_bench::clock::SystemTimePoint>
    : public formatter<string_view> {
    /*!
     * \brief Format.
     *
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    auto format(const stat_bench::clock::SystemTimePoint& val,
        format_context& context) const -> format_context::iterator;
};

}  // namespace fmt
