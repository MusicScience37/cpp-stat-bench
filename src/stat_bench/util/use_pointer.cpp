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
 * \brief Definition of use_pointer function.
 */
#include "stat_bench/util/use_pointer.h"

#include <atomic>

namespace stat_bench {
namespace util {

// Separate implementation to prevent optimization.

void use_pointer(void* ptr) noexcept {
    *reinterpret_cast<char volatile*>(ptr) =
        *reinterpret_cast<char volatile*>(ptr);
}

}  // namespace util
}  // namespace stat_bench
