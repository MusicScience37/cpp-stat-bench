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
 * \brief Definition of BenchmarkCaseInfo class.
 */
#pragma once

#include <cstddef>
#include <exception>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

#include "stat_bench/bench/benchmark_condition.h"
#include "stat_bench/clock/stop_watch.h"
#include "stat_bench/util/memory_barrier.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Class of context of invocations of benchmarks.
 */
class InvocationContext {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] cond Condition.
     * \param[in] iterations Number of iterations.
     * \param[in] samples Number of samples.
     */
    InvocationContext(
        BenchmarkCondition cond, std::size_t iterations, std::size_t samples)
        : cond_(cond), iterations_(iterations), samples_(samples) {}

    InvocationContext(const InvocationContext&) = delete;
    InvocationContext(InvocationContext&&) = delete;
    auto operator=(const InvocationContext&) = delete;
    auto operator=(InvocationContext&&) = delete;

    /*!
     * \brief Destructor.
     */
    ~InvocationContext() = default;

    /*!
     * \brief Get the number of threads.
     *
     * \return Number of threads.
     */
    [[nodiscard]] auto threads() const noexcept -> std::size_t {
        return cond_.threads();
    }

    /*!
     * \brief Get the number of iterations.
     *
     * \return Number of iterations.
     */
    [[nodiscard]] auto iterations() const noexcept -> std::size_t {
        return iterations_;
    }

    /*!
     * \brief Get the number of samples.
     *
     * \return Number of samples.
     */
    [[nodiscard]] auto samples() const noexcept -> std::size_t {
        return samples_;
    }

    /*!
     * \brief Measure time.
     *
     * \tparam Func Type of function.
     * \param[in] func Function.
     */
    template <typename Func>
    void measure(const Func& func) {
        durations_.clear();

        if (cond_.threads() == 1) {
            measure_here(func, 0);
        } else {
            std::vector<std::thread> threads;
            threads.reserve(cond_.threads());
            std::exception_ptr error;
            try {
                for (std::size_t i = 0; i < cond_.threads(); ++i) {
                    threads.emplace_back(
                        [this, &func, i] { this->measure_here(func, i); });
                }
            } catch (...) {
                error = std::current_exception();
            }

            for (std::size_t i = 0; i < cond_.threads(); ++i) {
                if (threads.at(i).joinable()) {
                    threads.at(i).join();
                }
            }

            if (error) {
                std::rethrow_exception(error);
            }
        }
    }

    /*!
     * \brief Get the measured durations.
     *
     * \note Duration of iterations in each sample is measured per thread.
     *
     * \return Durations.
     */
    [[nodiscard]] auto durations() const noexcept
        -> const std::vector<std::vector<clock::Duration>>& {
        return durations_;
    }

private:
    /*!
     * \brief Measure time in the current thread.
     *
     * \tparam Func Type of function.
     * \param[in] func Function.
     * \param[in] thread_index Index of the thread.
     */
    template <typename Func>
    void measure_here(const Func& func, std::size_t thread_index) {
        clock::StopWatch watch;
        watch.start(samples_);
        for (std::size_t sample_index = 0; sample_index < samples_;
             ++sample_index) {
            util::memory_barrier();
            for (std::size_t iteration_index = 0; iteration_index < iterations_;
                 ++iteration_index) {
                func(thread_index, sample_index, iteration_index);
            }
            util::memory_barrier();
            watch.lap();
        }

        std::unique_lock<std::mutex> lock(durations_mutex_);
        durations_.push_back(watch.calc_durations());
    }

    //! Condition.
    BenchmarkCondition cond_;

    //! Number of iterations.
    std::size_t iterations_;

    //! Number of samples.
    std::size_t samples_;

    //! Measured durations.
    std::vector<std::vector<clock::Duration>> durations_{};

    //! Mutex for durations.
    std::mutex durations_mutex_{};
};

}  // namespace bench
}  // namespace stat_bench
