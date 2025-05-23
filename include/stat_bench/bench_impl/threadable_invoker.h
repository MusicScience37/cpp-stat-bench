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

// IWYU pragma: no_include <version>

#include <cstdlib>
#include <exception>
#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/stop_watch.h"
#include "stat_bench/do_not_optimize.h"
#include "stat_bench/memory_barrier.h"
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/sync_barrier.h"

namespace stat_bench {
namespace bench_impl {

// Define invoke_result_t for C++14 and C++17
#if defined(__cpp_lib_is_invocable) || defined(STAT_BENCH_DOCUMENTATION)
// Since C++17
/*!
 * \brief Get the result type of invoking a function with arguments.
 *
 * \tparam Func Type of the function.
 * \tparam Args Type of the arguments.
 */
template <typename Func, typename... Args>
using invoke_result_t = std::invoke_result_t<Func, Args...>;
#else
// C++14
template <typename Func, typename... Args>
using invoke_result_t = std::result_of_t<Func(Args...)>;  // NOLINT
#endif

// Define invoke_result_t for C++14 and C++17
#ifdef STAT_BENCH_DOCUMENTATION
/*!
 * \brief Invoke a function and ignore the return value.
 *
 * \tparam Func Type of the function.
 * \tparam Args Type of the arguments.
 * \param[in] func Function.
 * \param[in] args Arguments.
 */
template <typename Func, typename... Args>
void invoke_and_ignore_return_value(const Func& func, Args&&... args) {
    do_not_optimize(func(std::forward<Args>(args)...));
}
#else
/*!
 * \brief Invoke a function and ignore the return value.
 *
 * \tparam Func Type of the function.
 * \tparam Args Type of the arguments.
 * \param[in] func Function.
 * \param[in] args Arguments.
 *
 * \note This version is called when the return value of the function is void.
 */
template <typename Func, typename... Args>
auto invoke_and_ignore_return_value(const Func& func, Args&&... args)
    -> std::enable_if_t<
        // NOLINTNEXTLINE(modernize-type-traits): is_same_v is unavailable in C++14.
        std::is_same<invoke_result_t<Func, Args...>, void>::value> {
    func(std::forward<Args>(args)...);
}

/*!
 * \brief Invoke a function and ignore the return value.
 *
 * \tparam Func Type of the function.
 * \tparam Args Type of the arguments.
 * \param[in] func Function.
 * \param[in] args Arguments.
 *
 * \note This version is called when the return value of the function is not
 * void.
 */
template <typename Func, typename... Args>
auto invoke_and_ignore_return_value(const Func& func, Args&&... args)
    -> std::enable_if_t<
        // NOLINTNEXTLINE(modernize-type-traits): is_same_v is unavailable in C++14.
        !std::is_same<invoke_result_t<Func, Args...>, void>::value> {
    do_not_optimize(func(std::forward<Args>(args)...));
}
#endif

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
        if (num_threads_ >= 2U) {
            barrier_ = util::create_sync_barrier(num_threads_);
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
                threads.emplace_back([this, &func, i, &promises]() {
                    barrier_->wait();
                    measure_here(func, i, promises[i]);
                });
            }
        } catch (const std::exception& e) {
            // If thread cannot be created, nothing can be done here.
            std::cerr << e.what()
                      << std::endl;  // NOLINT(performance-avoid-endl)
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
            memory_barrier();
            for (std::size_t iteration_index = 0; iteration_index < iterations_;
                ++iteration_index) {
                invoke_and_ignore_return_value(
                    func, thread_index, sample_index, iteration_index);
            }
            memory_barrier();
        }

        // actual measurement
        watch.start(samples_);
        for (; sample_index < samples_; ++sample_index) {
            memory_barrier();
            for (std::size_t iteration_index = 0; iteration_index < iterations_;
                ++iteration_index) {
                invoke_and_ignore_return_value(
                    func, thread_index, sample_index, iteration_index);
            }
            memory_barrier();
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
        std::promise<std::vector<clock::Duration>>& promise) const {
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

    //! Barrier to synchronize threads.
    std::shared_ptr<util::ISyncBarrier> barrier_;
};

}  // namespace bench_impl
}  // namespace stat_bench
