/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
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
 * \brief Definition of PthreadSyncBarrier class. (Internal header.)
 */
#pragma once

#include <cstddef>

#include <fmt/format.h>
#include <pthread.h>

#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/sync_barrier.h"

namespace stat_bench::util {

/*!
 * \brief Class of barriers to synchronize threads using pthread library.
 */
class PthreadSyncBarrier final : public ISyncBarrier {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] num_waiting_threads Number of threads to wait.
     */
    explicit PthreadSyncBarrier(std::size_t num_waiting_threads) {
        if (num_waiting_threads < 2U) {
            throw StatBenchException(
                "Invalid number of threads to wait in PthreadSyncBarrier.");
        }
        const int error_code = pthread_barrier_init(
            &barrier_, nullptr, static_cast<unsigned int>(num_waiting_threads));
        if (error_code != 0) {
            throw StatBenchException(fmt::format(
                "Failed to initialize PthreadSyncBarrier (error code: {}).",
                error_code));
        }
    }

    /*!
     * \brief Wait for other threads.
     */
    void wait() override { pthread_barrier_wait(&barrier_); }

    PthreadSyncBarrier(const PthreadSyncBarrier&) = delete;
    PthreadSyncBarrier(PthreadSyncBarrier&&) = delete;
    auto operator=(const PthreadSyncBarrier&) = delete;
    auto operator=(PthreadSyncBarrier&&) = delete;

    //! Destructor.
    ~PthreadSyncBarrier() override { pthread_barrier_destroy(&barrier_); }

private:
    //! Barrier.
    pthread_barrier_t barrier_{};
};

}  // namespace stat_bench::util
