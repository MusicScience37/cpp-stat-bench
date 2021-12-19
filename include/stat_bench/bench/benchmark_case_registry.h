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
 * \brief Definition of BenchmarkCaseRegistry class.
 */
#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "stat_bench/bench/benchmark_group.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Class of registry of cases of benchmarks.
 */
class BenchmarkCaseRegistry {
public:
    /*!
     * \brief Constructor.
     */
    BenchmarkCaseRegistry() = default;

    /*!
     * \brief Add a case.
     *
     * \param[in] bench_case Case.
     */
    void add(std::shared_ptr<IBenchmarkCase> bench_case) {
        const auto& group_name = bench_case->info().group_name();
        auto iter = std::lower_bound(groups_.begin(), groups_.end(), group_name,
            [](const BenchmarkGroup& group, const std::string& group_name_in) {
                return group.name() < group_name_in;
            });
        if (iter != groups_.end() && iter->name() == group_name) {
            iter->add(std::move(bench_case));
            return;
        }

        iter = std::upper_bound(groups_.begin(), groups_.end(), group_name,
            [](const std::string& group_name_in, const BenchmarkGroup& group) {
                return group_name_in < group.name();
            });
        iter = groups_.emplace(iter, group_name);
        iter->add(std::move(bench_case));
    }

    /*!
     * \brief Get benchmarks.
     *
     * \return Benchmarks per group.
     */
    [[nodiscard]] auto benchmarks() const noexcept
        -> const std::vector<BenchmarkGroup>& {
        return groups_;
    }

    /*!
     * \brief Get an instance of the registry.
     *
     * \return Reference to the instance.
     */
    [[nodiscard]] static auto instance() -> BenchmarkCaseRegistry& {
        static BenchmarkCaseRegistry registry;
        return registry;
    }

private:
    //! Groups.
    std::vector<BenchmarkGroup> groups_{};
};

}  // namespace bench
}  // namespace stat_bench
