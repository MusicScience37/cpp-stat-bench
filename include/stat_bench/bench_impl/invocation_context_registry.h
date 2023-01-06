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
 * \brief Definition of InvocationContextRegistry class.
 */
#pragma once

#include <memory>

#include "stat_bench/invocation_context.h"

namespace stat_bench {
namespace bench_impl {

/*!
 * \brief Class to save InvocationContext object.
 */
class InvocationContextRegistry {
public:
    /*!
     * \brief Get the global instance.
     *
     * \return Reference to the instance.
     */
    static auto instance() -> InvocationContextRegistry&;

    /*!
     * \brief Create a context.
     *
     * \param[in] cond Condition.
     * \param[in] iterations Number of iterations.
     * \param[in] samples Number of samples (including warming up).
     * \param[in] warming_up_samples Number of samples for warming up.
     * \return Created context.
     */
    auto create(BenchmarkCondition cond, std::size_t iterations,
        std::size_t samples, std::size_t warming_up_samples)
        -> InvocationContext&;

    /*!
     * \brief Remove the context.
     */
    void clear() noexcept;

    /*!
     * \brief Get the context.
     *
     * \return Context.
     */
    [[nodiscard]] auto get() const -> InvocationContext&;

    InvocationContextRegistry(const InvocationContextRegistry&) = delete;
    InvocationContextRegistry(InvocationContextRegistry&&) = delete;
    auto operator=(const InvocationContextRegistry&) = delete;
    auto operator=(InvocationContextRegistry&&) = delete;

private:
    //! Constructor.
    InvocationContextRegistry();

    //! Destructor.
    ~InvocationContextRegistry() = default;

    //! Context.
    std::unique_ptr<InvocationContext> context_;
};

}  // namespace bench_impl
}  // namespace stat_bench
