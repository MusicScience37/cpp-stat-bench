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
 * \brief Definition of memory_barrier function.
 */
#pragma once

#include <atomic>

namespace stat_bench {
namespace util {

/*!
 * \brief Prevent optimizers to move memory access beyond this function call.
 */
inline void memory_barrier() noexcept {
    std::atomic_signal_fence(std::memory_order_acq_rel);
}

}  // namespace util
}  // namespace stat_bench
