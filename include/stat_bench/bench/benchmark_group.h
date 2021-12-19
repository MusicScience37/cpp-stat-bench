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
 * \brief Definition of BenchmarkGroup class.
 */
#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "stat_bench/bench/i_benchmark_case.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Class of groups of cases in benchmarks.
 */
class BenchmarkGroup {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] name Name.
     */
    explicit BenchmarkGroup(std::string name) : name_(std::move(name)) {}

    /*!
     * \brief Get the group name.
     *
     * \return Group name.
     */
    [[nodiscard]] auto name() const noexcept -> const std::string& {
        return name_;
    }

    /*!
     * \brief Add a case.
     *
     * \param[in] bench_case Case.
     */
    void add(std::shared_ptr<IBenchmarkCase> bench_case) {
        const auto iter =
            std::upper_bound(cases_.begin(), cases_.end(), bench_case,
                [](const std::shared_ptr<IBenchmarkCase>& left,
                    const std::shared_ptr<IBenchmarkCase>& right) {
                    return left->info().case_name() < right->info().case_name();
                });
        cases_.insert(iter, std::move(bench_case));
    }

    /*!
     * \brief Get cases.
     *
     * \return Cases.
     */
    [[nodiscard]] auto cases() const noexcept
        -> const std::vector<std::shared_ptr<IBenchmarkCase>>& {
        return cases_;
    }

private:
    //! Name.
    std::string name_;

    //! Cases.
    std::vector<std::shared_ptr<IBenchmarkCase>> cases_{};
};

}  // namespace bench
}  // namespace stat_bench
