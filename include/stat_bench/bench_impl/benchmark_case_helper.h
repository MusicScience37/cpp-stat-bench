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

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"

namespace stat_bench::bench_impl {

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
    BenchCaseHelper(const BenchmarkGroupName& group_name,
        const BenchmarkCaseName& case_name)
        : info_(group_name, case_name) {}

private:
    //! \copydoc stat_bench::bench_impl::IBenchmarkCase::info
    [[nodiscard]] auto info() const noexcept -> const BenchmarkFullName& final {
        return info_;
    }

    //! Information of this case.
    BenchmarkFullName info_;
};

}  // namespace stat_bench::bench_impl
