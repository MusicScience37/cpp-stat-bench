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
 * \brief Definition of SyncBarrier class.
 */
#pragma once

#include <condition_variable>
#include <cstddef>
#include <memory>
#include <mutex>

namespace stat_bench {
namespace util {

/*!
 * \brief Interface of barriers to synchronize threads.
 */
class ISyncBarrier {
public:
    /*!
     * \brief Wait for other threads.
     */
    virtual void wait() = 0;

    ISyncBarrier(const ISyncBarrier&) = delete;
    ISyncBarrier(ISyncBarrier&&) = delete;
    auto operator=(const ISyncBarrier&) = delete;
    auto operator=(ISyncBarrier&&) = delete;

    //! Destructor.
    virtual ~ISyncBarrier() = default;

protected:
    //! Constructor.
    ISyncBarrier() = default;
};

/*!
 * \brief Create a barrier to synchronize threads using a mutex.
 *
 * \param[in] num_waiting_threads Number of threads to wait.
 * \return Barrier.
 */
[[nodiscard]] auto create_mutex_sync_barrier(std::size_t num_waiting_threads)
    -> std::shared_ptr<ISyncBarrier>;

/*!
 * \brief Create a barrier to synchronize threads.
 *
 * \param[in] num_waiting_threads Number of threads to wait.
 * \return Barrier.
 */
[[nodiscard]] auto create_sync_barrier(std::size_t num_waiting_threads)
    -> std::shared_ptr<ISyncBarrier>;

}  // namespace util
}  // namespace stat_bench
