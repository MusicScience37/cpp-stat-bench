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
     * \param[in] seconds Number of seconds.
     */
    explicit Duration(double seconds) noexcept : seconds_(seconds) {}

    /*!
     * \brief Get the number of seconds.
     *
     * \return Number of seconds.
     */
    [[nodiscard]] auto seconds() const noexcept -> double { return seconds_; }

private:
    //! Number of seconds.
    double seconds_;
};

}  // namespace clock
}  // namespace stat_bench
