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
 * \brief Definition of GlobFilter class.
 */
#pragma once

#include <string>

#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/filters/i_name_filter.h"

namespace stat_bench {
namespace filters {

/*!
 * \brief Class of filters using glob patterns.
 */
class GlobFilter final : public INameFilter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] pattern Glob pattern.
     */
    explicit GlobFilter(std::string pattern);

    //! \copydoc stat_bench::filters::INameFilter::check
    [[nodiscard]] auto check(const BenchmarkFullName& name) const
        -> bool override;

    GlobFilter(const GlobFilter&) = delete;
    GlobFilter(GlobFilter&&) = delete;
    auto operator=(const GlobFilter&) -> GlobFilter& = delete;
    auto operator=(GlobFilter&&) -> GlobFilter& = delete;

    /*!
     * \brief Destructor.
     */
    ~GlobFilter() override = default;

private:
    //! Glob pattern.
    std::string pattern_;
};

}  // namespace filters
}  // namespace stat_bench
