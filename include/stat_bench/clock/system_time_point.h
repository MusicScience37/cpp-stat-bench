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
#include <string>

#include <fmt/chrono.h>
#include <fmt/core.h>
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
     * \brief Format to string.
     *
     * \tparam OutputIter Type of the output iterator.
     * \param[in] iter Output iterator.
     * \return Output iterator after formatting.
     */
    template <typename OutputIter>
    // NOLINTNEXTLINE(modernize-use-nodiscard) : API for the external library.
    auto format_to(OutputIter iter) const -> OutputIter {
        const auto time_sec =
            std::chrono::time_point_cast<std::chrono::seconds>(time_point_);
        const auto time_tm =
            fmt::localtime(std::chrono::system_clock::to_time_t(time_sec));
        const auto time_usec =
            std::chrono::duration_cast<std::chrono::microseconds>(
                time_point_ - time_sec)
                .count();

        return fmt::format_to(
            iter, "{0:%FT%T}.{1:06d}{0:%z}", time_tm, time_usec);
    }

private:
    //! Actual time point.
    std::chrono::system_clock::time_point time_point_;
};

}  // namespace clock
}  // namespace stat_bench

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for
 * stat_bench::clock::SystemTimePoint.
 */
template <>
struct formatter<stat_bench::clock::SystemTimePoint>
    : public formatter<std::string> {
    /*!
     * \brief Format.
     *
     * \tparam FormatContext Type of the context.
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    template <typename FormatContext>
    auto format(const stat_bench::clock::SystemTimePoint& val,
        FormatContext& context) const -> decltype(context.out()) {
        return val.format_to(context.out());
    }
};

}  // namespace fmt
