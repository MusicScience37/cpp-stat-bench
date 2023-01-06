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
 * \brief Definition of ComposedFilter class.
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "stat_bench/filters/i_name_filter.h"

namespace stat_bench {
namespace filters {

/*!
 * \brief Class of composed filters of benchmarks.
 */
class ComposedFilter {
public:
    /*!
     * \brief Constructor.
     */
    ComposedFilter() = default;

    /*!
     * \brief Add a filter of benchmark names to include using regular
     * expressions.
     *
     * \param[in] regex Regular expression.
     */
    void include_with_regex(const std::string& regex);

    /*!
     * \brief Add a filter of benchmark names to exclude using regular
     * expressions.
     *
     * \param[in] regex Regular expression.
     */
    void exclude_with_regex(const std::string& regex);

    /*!
     * \brief Check whether a name matches to this filter.
     *
     * \param[in] name Name.
     * \retval true Input matched to this filter.
     * \retval false Input didn't match to this filter.
     */
    [[nodiscard]] auto check(const BenchmarkFullName& name) const -> bool;

private:
    //! Filter of benchmark names to include.
    std::vector<std::shared_ptr<INameFilter>> included_filter_{};

    //! Filter of benchmark names to exclude.
    std::vector<std::shared_ptr<INameFilter>> excluded_filter_{};
};

}  // namespace filters
}  // namespace stat_bench
