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
 * \brief Test of SyncBarrier class.
 */
#include "stat_bench/util/sync_barrier.h"

#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("stat_bench::util::ISyncBarrier") {
    using stat_bench::util::ISyncBarrier;

    using Factory = std::shared_ptr<ISyncBarrier>(std::size_t);
    Factory* factory = GENERATE(&stat_bench::util::create_mutex_sync_barrier,
        &stat_bench::util::create_sync_barrier);

    SECTION("validate number of threads") {
        CHECK_THROWS((void)factory(0));
        CHECK_THROWS((void)factory(1));
        CHECK_NOTHROW((void)factory(2));
        CHECK_NOTHROW((void)factory(3));
    }

    SECTION("wait") {
        static constexpr std::size_t num_threads = 3;
        auto barrier = factory(num_threads);

        std::mutex mutex{};
        std::condition_variable cond_var{};
        std::size_t state = 0;
        std::size_t finished = 0;
        static constexpr auto timeout = std::chrono::seconds(10);

        std::vector<std::thread> threads;
        threads.reserve(num_threads);
        for (std::size_t i = 0; i < num_threads; ++i) {
            threads.emplace_back(
                [barrier, &mutex, &cond_var, &state, &finished, index = i] {
                    std::unique_lock<std::mutex> lock(mutex);
                    if (!cond_var.wait_for(lock, timeout,
                            [&state, &index] { return state > index; })) {
                        std::abort();
                        return;
                    }
                    lock.unlock();

                    barrier->wait();

                    lock.lock();
                    ++finished;
                    lock.unlock();
                    cond_var.notify_all();
                });
        }

        std::unique_lock<std::mutex> lock(mutex);
        state = num_threads - 1;
        lock.unlock();
        cond_var.notify_all();

        static constexpr auto check_time = std::chrono::milliseconds(100);
        lock.lock();
        cond_var.wait_for(
            lock, check_time, [&finished] { return finished > 0; });
        CHECK(finished == 0);
        lock.unlock();

        lock.lock();
        state = num_threads;
        lock.unlock();
        cond_var.notify_all();

        lock.lock();
        cond_var.wait_for(
            lock, timeout, [&finished] { return finished == num_threads; });
        REQUIRE(finished == num_threads);
        lock.unlock();

        for (auto& thread : threads) {
            thread.join();
        }
    }
}
