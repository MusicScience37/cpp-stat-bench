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
 * \brief Definition of ThreadableInvoker class.
 */
#pragma once

#include <exception>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/stop_watch.h"
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/memory_barrier.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Class to invoke functions measuring durations in threads if needed.
 */
class ThreadableInvoker {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] num_threads Number of threads.
     * \param[in] iterations Number of iterations.
     * \param[in] samples Number of samples (including samples for warming up).
     * \param[in] warm_up_samples Number of samples for warming up.
     */
    ThreadableInvoker(std::size_t num_threads, std::size_t iterations,
        std::size_t samples, std::size_t warm_up_samples)
        : num_threads_(num_threads),
          iterations_(iterations),
          samples_(samples),
          warm_up_samples_(warm_up_samples) {
        if (num_threads_ == 0) {
            throw StatBenchException("Number of threads must be at least one.");
        }
        if (iterations_ == 0) {
            throw StatBenchException(
                "Number of iterations must be at least one.");
        }
        if (samples_ == 0) {
            throw StatBenchException("Number of samples must be at least one.");
        }
        if (samples_ <= warm_up_samples) {
            throw StatBenchException(
                "Number of samples for measurement must be at least one.");
        }
    }

    /*!
     * \brief Measure time.
     *
     * \tparam Func Type of function.
     * \param[in] func Function.
     * \return Measured durations per thread.
     */
    template <typename Func>
    [[nodiscard]] auto measure(const Func& func) const
        -> std::vector<std::vector<clock::Duration>> {
        if (num_threads_ == 1) {
            return std::vector<std::vector<clock::Duration>>{
                measure_here(func, 0)};
        }

        std::vector<std::promise<std::vector<clock::Duration>>> promises;
        promises.resize(num_threads_);
        std::vector<std::future<std::vector<clock::Duration>>> futures;
        futures.reserve(num_threads_);
        for (auto& promise : promises) {
            futures.push_back(promise.get_future());
        }

        std::vector<std::thread> threads;
        threads.reserve(num_threads_);
        std::exception_ptr error;
        try {
            for (std::size_t i = 0; i < num_threads_; ++i) {
                threads.emplace_back([this, &func, i, &promises]() noexcept {
                    measure_here(func, i, promises[i]);
                });
            }
        } catch (const std::exception& e) {
            // If thread cannot be created, nothing can be done here.
            std::cerr << e.what() << std::endl;
            std::abort();
        }
        for (auto& thread : threads) {
            thread.join();
        }

        std::vector<std::vector<clock::Duration>> durations;
        durations.reserve(num_threads_);
        for (auto& future : futures) {
            durations.push_back(future.get());
        }
        return durations;
    }

private:
    /*!
     * \brief Measure time in the current thread.
     *
     * \tparam Func Type of the function.
     * \param[in] func Function.
     * \param[in] thread_index Index of this thread.
     * \return Measured durations.
     */
    template <typename Func>
    [[nodiscard]] auto measure_here(const Func& func,
        std::size_t thread_index) const -> std::vector<clock::Duration> {
        clock::StopWatch watch;

        // warming up
        std::size_t sample_index = 0;
        for (; sample_index < warm_up_samples_; ++sample_index) {
            util::memory_barrier();
            for (std::size_t iteration_index = 0; iteration_index < iterations_;
                 ++iteration_index) {
                func(thread_index, sample_index, iteration_index);
            }
            util::memory_barrier();
        }

        // actual measurement
        watch.start(samples_);
        for (; sample_index < samples_; ++sample_index) {
            util::memory_barrier();
            for (std::size_t iteration_index = 0; iteration_index < iterations_;
                 ++iteration_index) {
                func(thread_index, sample_index, iteration_index);
            }
            util::memory_barrier();
            watch.lap();
        }
        return watch.calc_durations();
    }

    /*!
     * \brief Measure time in the current thread.
     *
     * \tparam Func Type of the function.
     * \param[in] func Function.
     * \param[in] thread_index Index of this thread.
     * \param[out] promise Promise object to store the result.
     */
    template <typename Func>
    void measure_here(const Func& func, std::size_t thread_index,
        std::promise<std::vector<clock::Duration>>& promise) const noexcept {
        try {
            promise.set_value(measure_here(func, thread_index));
        } catch (...) {
            promise.set_exception(std::current_exception());
        }
    }

    //! Number of threads.
    std::size_t num_threads_;

    //! Number of iterations.
    std::size_t iterations_;

    //! Number of samples (including samples for warming up).
    std::size_t samples_;

    //! Number of samples for warming up.
    std::size_t warm_up_samples_;
};

}  // namespace bench
}  // namespace stat_bench
