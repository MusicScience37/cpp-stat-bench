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
 * \brief Implementation of BenchmarkCaseRegistry class.
 */
#include "stat_bench/bench_impl/benchmark_case_registry.h"

#include <algorithm>
#include <string>
#include <type_traits>
#include <utility>

#include "stat_bench/benchmark_full_name.h"

namespace stat_bench {
namespace bench_impl {

void BenchmarkCaseRegistry::add(std::shared_ptr<IBenchmarkCase> bench_case) {
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

void BenchmarkCaseRegistry::filter_by(const filters::ComposedFilter& filter) {
    for (auto iter = groups_.begin(); iter < groups_.end();) {
        auto& group = *iter;
        group.filter_by(filter);
        if (group.cases().empty()) {
            iter = groups_.erase(iter);
        } else {
            ++iter;
        }
    }
}

auto BenchmarkCaseRegistry::benchmarks() const noexcept
    -> const std::vector<BenchmarkGroup>& {
    return groups_;
}
auto BenchmarkCaseRegistry::instance() -> BenchmarkCaseRegistry& {
    static BenchmarkCaseRegistry registry;
    return registry;
}

}  // namespace bench_impl
}  // namespace stat_bench
