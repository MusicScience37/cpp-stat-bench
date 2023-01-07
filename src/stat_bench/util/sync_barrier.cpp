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
 * \brief Implementation of SyncBarrier class.
 */
#include "stat_bench/util/sync_barrier.h"

#include <memory>
#include <mutex>

#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace util {

/*!
 * \brief Class of barriers to synchronize threads using mutexes.
 */
class MutexSyncBarrier final : public ISyncBarrier {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] num_waiting_threads Number of threads to wait.
     */
    explicit MutexSyncBarrier(std::size_t num_waiting_threads)
        : num_waiting_threads_(num_waiting_threads) {
        if (num_waiting_threads < 2U) {
            throw StatBenchException(
                "Invalid number of threads to wait in MutexSyncBarrier.");
        }
    }

    /*!
     * \brief Wait for other threads.
     */
    void wait() override {
        std::unique_lock<std::mutex> lock(mutex_);
        if (num_remaining_threads_ == 0U) {
            // This is the first thread to wait.
            num_remaining_threads_ = num_waiting_threads_ - 1U;
            cond_var_.wait(
                lock, [this] { return num_remaining_threads_ == 0U; });
        } else if (num_remaining_threads_ == 1U) {
            // This is the last thread to wait.
            num_remaining_threads_ = 0U;
            lock.unlock();
            cond_var_.notify_all();
        } else {
            --num_remaining_threads_;
            cond_var_.wait(
                lock, [this] { return num_remaining_threads_ == 0U; });
        }
    }

    MutexSyncBarrier(const MutexSyncBarrier&) = delete;
    MutexSyncBarrier(MutexSyncBarrier&&) = delete;
    auto operator=(const MutexSyncBarrier&) = delete;
    auto operator=(MutexSyncBarrier&&) = delete;

    //! Destructor.
    ~MutexSyncBarrier() override = default;

private:
    //! Mutex.
    std::mutex mutex_{};

    //! Condition variable.
    std::condition_variable cond_var_{};

    //! Number of threads to wait.
    std::size_t num_waiting_threads_;

    //! Number of remaining threads.
    std::size_t num_remaining_threads_{0};
};

auto create_mutex_sync_barrier(std::size_t num_waiting_threads)
    -> std::shared_ptr<ISyncBarrier> {
    return std::make_shared<MutexSyncBarrier>(num_waiting_threads);
}

auto create_sync_barrier(std::size_t num_waiting_threads)
    -> std::shared_ptr<ISyncBarrier> {
    return create_mutex_sync_barrier(num_waiting_threads);
}

}  // namespace util
}  // namespace stat_bench
