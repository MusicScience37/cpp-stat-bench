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
 * \brief Definition of STAT_BENCH_IMPL_MEASURE_IMPL macro.
 */
#pragma once

#include "stat_bench/current_invocation_context.h"
#include "stat_bench/invocation_context.h"

namespace stat_bench {
namespace impl {

/*!
 * \brief Helper class to measure a function.
 */
class FunctionMeasurer {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] context Context.
     */
    explicit FunctionMeasurer(
        InvocationContext& context = current_invocation_context())
        : context_(context) {}

    /*!
     * \brief Measure a function.
     *
     * \tparam Func Type of the function.
     * \param[in] func Function.
     */
    template <typename Func>
    void operator<<(const Func& func) {
        context_.measure(func);
    }

private:
    //! Context.
    InvocationContext& context_;
};

}  // namespace impl
}  // namespace stat_bench

/*!
 * \brief Macro to measure a function.
 *
 * \param[in] THREAD_INDEX_VAR Variable name of the index of the thread.
 * \param[in] SAMPLE_INDEX_VAR Variable name of the index of the sample.
 * \param[in] ITERATION_INDEX_VAR Variable name of the index of the iteration.
 */
#define STAT_BENCH_IMPL_MEASURE_IMPL(                                      \
    THREAD_INDEX_VAR, SAMPLE_INDEX_VAR, ITERATION_INDEX_VAR)               \
    ::stat_bench::impl::FunctionMeasurer()                                 \
        << [&](std::size_t THREAD_INDEX_VAR, std::size_t SAMPLE_INDEX_VAR, \
               std::size_t ITERATION_INDEX_VAR)
