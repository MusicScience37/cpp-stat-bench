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
 * \brief Definition of StopWatch class.
 */
#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/monotone_clock.h"
#include "stat_bench/clock/monotone_time_point.h"

namespace stat_bench {
namespace clock {

/*!
 * \brief Class of a stop watch.
 */
class StopWatch {
public:
    /*!
     * \brief Constructor.
     */
    StopWatch() = default;

    StopWatch(const StopWatch&) = delete;
    StopWatch(StopWatch&&) = delete;
    auto operator=(const StopWatch&) -> StopWatch& = delete;
    auto operator=(StopWatch&&) -> StopWatch& = delete;

    /*!
     * \brief Destructor.
     */
    ~StopWatch() = default;

    /*!
     * \brief Start measurement.
     *
     * \note This will reserve memory storage for laps.
     *
     * \param[in] num_laps Number of laps.
     */
    void start(std::size_t num_laps) {
        time_points_.clear();
        time_points_.reserve(num_laps + 1);
        lap();
    }

    /*!
     * \brief Measure a time point for a lap.
     */
    void lap() { time_points_.push_back(MonotoneClock::now()); }

    /*!
     * \brief Calculate measured durations.
     *
     * \return Durations.
     */
    [[nodiscard]] auto calc_durations() const {
        if (time_points_.size() < 2) {
            throw std::runtime_error("Too few number of time points.");
        }
        std::vector<Duration> durations;
        durations.reserve(time_points_.size() - 1);
        for (std::size_t i = 0; i < time_points_.size() - 1; ++i) {
            durations.push_back(time_points_[i + 1] - time_points_[i]);
        }
        return durations;
    }

private:
    //! Time points.
    std::vector<MonotoneTimePoint> time_points_{};
};

}  // namespace clock
}  // namespace stat_bench
