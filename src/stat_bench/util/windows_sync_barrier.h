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
 * \brief Definition of WindowsSyncBarrier class. (Internal header.)
 */
#pragma once

#include <Windows.h>
#include <fmt/format.h>
#include <synchapi.h>

#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/sync_barrier.h"

namespace stat_bench {
namespace util {

/*!
 * \brief Class of barriers to synchronize threads using synchronization
 * barriers in Windows.
 */
class WindowsSyncBarrier final : public ISyncBarrier {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] num_waiting_threads Number of threads to wait.
     */
    explicit WindowsSyncBarrier(std::size_t num_waiting_threads) {
        if (num_waiting_threads < 2U) {
            throw StatBenchException(
                "Invalid number of threads to wait in WindowsSyncBarrier.");
        }
        BOOL result = InitializeSynchronizationBarrier(
            &barrier_, static_cast<LONG>(num_waiting_threads), -1);
        if (result == FALSE) {
            throw StatBenchException(fmt::format(
                "Failed to initialize WindowsSyncBarrier (error code: {}).",
                GetLastError()));
        }
    }

    /*!
     * \brief Wait for other threads.
     */
    void wait() override { EnterSynchronizationBarrier(&barrier_, 0); }

    WindowsSyncBarrier(const WindowsSyncBarrier&) = delete;
    WindowsSyncBarrier(WindowsSyncBarrier&&) = delete;
    auto operator=(const WindowsSyncBarrier&) = delete;
    auto operator=(WindowsSyncBarrier&&) = delete;

    //! Destructor.
    ~WindowsSyncBarrier() override { DeleteSynchronizationBarrier(&barrier_); }

private:
    //! Barrier.
    SYNCHRONIZATION_BARRIER barrier_{};
};

}  // namespace util
}  // namespace stat_bench
