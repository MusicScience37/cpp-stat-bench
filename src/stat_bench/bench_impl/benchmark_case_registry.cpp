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

#include <utility>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"

namespace stat_bench {
namespace bench_impl {

void BenchmarkCaseRegistry::add(std::shared_ptr<IBenchmarkCase> bench_case) {
    const auto& group_name = bench_case->info().group_name();
    auto& group = add_or_get_group(group_name);
    group.add(std::move(bench_case));
}

auto BenchmarkCaseRegistry::add_or_get_group(const BenchmarkGroupName& name)
    -> BenchmarkGroup& {
    const auto [iter, inserted] = groups_.try_emplace(name, name);
    return iter->second;
}

void BenchmarkCaseRegistry::filter_by(const filters::ComposedFilter& filter) {
    for (auto iter = groups_.begin(); iter < groups_.end();) {
        auto& group = iter->second;
        group.filter_by(filter);
        if (group.cases().empty()) {
            iter = groups_.erase(iter);
        } else {
            ++iter;
        }
    }
}

auto BenchmarkCaseRegistry::benchmarks() const noexcept
    -> const util::OrderedMap<BenchmarkGroupName, BenchmarkGroup>& {
    return groups_;
}

auto BenchmarkCaseRegistry::instance() -> BenchmarkCaseRegistry& {
    static BenchmarkCaseRegistry registry;
    return registry;
}

}  // namespace bench_impl
}  // namespace stat_bench
