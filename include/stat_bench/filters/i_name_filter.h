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
 * \brief Definition of INameFilter class.
 */
#pragma once

#include "stat_bench/bench/benchmark_full_name.h"

namespace stat_bench {
namespace filters {

/*!
 * \brief Interface of filters of names of benchmarks.
 */
class INameFilter {
public:
    /*!
     * \brief Check whether a name matches to this filter.
     *
     * \param[in] name Name.
     * \retval true Input matched to this filter.
     * \retval false Input didn't match to this filter.
     */
    [[nodiscard]] virtual auto check(const bench::BenchmarkFullName& name) const
        -> bool = 0;

    INameFilter(const INameFilter&) = delete;
    INameFilter(INameFilter&&) = delete;
    auto operator=(const INameFilter&) -> INameFilter& = delete;
    auto operator=(INameFilter&&) -> INameFilter& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~INameFilter() = default;

protected:
    /*!
     * \brief Constructor.
     */
    INameFilter() = default;
};

}  // namespace filters
}  // namespace stat_bench
