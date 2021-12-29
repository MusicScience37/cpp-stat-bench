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
 * \brief Definition of BenchCaseHelper class.
 */
#pragma once

#include <string>

#include "stat_bench/bench/benchmark_case_info.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Class to help definition of cases in benchmarks.
 *
 * \tparam Fixture Type of the fixture.
 */
template <typename Fixture>
class BenchCaseHelper : public Fixture {
protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] group_name Group name.
     * \param[in] case_name Case name.
     */
    BenchCaseHelper(const std::string& group_name, const std::string& case_name)
        : info_(group_name, case_name) {}

private:
    //! \copydoc stat_bench::bench::IBenchmarkCase::info
    [[nodiscard]] auto info() const noexcept
        -> const bench::BenchmarkCaseInfo& final {
        return info_;
    }

    //! Information of this case.
    bench::BenchmarkCaseInfo info_;
};

}  // namespace bench
}  // namespace stat_bench
