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
 * \brief Definition of IBenchmarkCase class.
 */
#pragma once

#include "stat_bench/bench/benchmark_case_info.h"
#include "stat_bench/bench/invocation_context.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Interface of cases in benchmarks.
 */
class IBenchmarkCase {
public:
    /*!
     * \brief Get information of this case.
     *
     * \return Information.
     */
    [[nodiscard]] virtual auto info() const noexcept
        -> const BenchmarkCaseInfo& = 0;

    /*!
     * \brief Invoke the function of this case.
     *
     * \param[in] context Context.
     */
    virtual void invoke(InvocationContext& context) = 0;

    IBenchmarkCase(const IBenchmarkCase&) = delete;
    IBenchmarkCase(IBenchmarkCase&&) = delete;
    auto operator=(const IBenchmarkCase&) -> IBenchmarkCase& = delete;
    auto operator=(IBenchmarkCase&&) -> IBenchmarkCase& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~IBenchmarkCase() = default;

protected:
    /*!
     * \brief Constructor.
     */
    IBenchmarkCase() = default;
};

}  // namespace bench
}  // namespace stat_bench
