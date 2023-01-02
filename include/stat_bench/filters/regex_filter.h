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
 * \brief Definition of RegexFilter class.
 */
#pragma once

#include <regex>
#include <string_view>

#include "stat_bench/bench/benchmark_full_name.h"
#include "stat_bench/filters/i_name_filter.h"

namespace stat_bench {
namespace filters {

/*!
 * \brief Class of filters using regular expressions.
 */
class RegexFilter final : public INameFilter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] regex Regular expression.
     */
    explicit RegexFilter(std::string_view regex);

    //! \copydoc stat_bench::filters::INameFilter::check
    [[nodiscard]] auto check(const bench::BenchmarkFullName& name) const
        -> bool override;

    RegexFilter(const RegexFilter&) = delete;
    RegexFilter(RegexFilter&&) = delete;
    auto operator=(const RegexFilter&) -> RegexFilter& = delete;
    auto operator=(RegexFilter&&) -> RegexFilter& = delete;

    /*!
     * \brief Destructor.
     */
    ~RegexFilter() override = default;

private:
    //! Regular expression.
    std::regex regex_;
};

}  // namespace filters
}  // namespace stat_bench
