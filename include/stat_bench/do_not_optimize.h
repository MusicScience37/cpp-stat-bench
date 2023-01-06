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
 * \brief Definition of do_not_optimize function.
 */
#pragma once

namespace stat_bench {
namespace impl {

/*!
 * \brief Use a pointer to prevent deletion of a variable.
 *
 * \param[in] ptr Pointer.
 */
void use_pointer(void* ptr) noexcept;

}  // namespace impl

/*!
 * \brief Prevent compilers to optimize away a value.
 *
 * \warning This won't prevent optimizations in processes to evaluate the value.
 *
 * \tparam T Type.
 * \param[in] val Value.
 */
template <typename T>
inline void do_not_optimize(T&& val) noexcept {
    impl::use_pointer(reinterpret_cast<void*>(&val));
}

}  // namespace stat_bench
