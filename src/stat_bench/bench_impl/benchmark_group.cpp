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
 * \brief Implementation of BenchmarkGroup class.
 */
#include "stat_bench/bench_impl/benchmark_group.h"

#include <utility>

#include <fmt/format.h>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace bench_impl {

BenchmarkGroup::BenchmarkGroup(BenchmarkGroupName name)
    : name_(std::move(name)) {}

auto BenchmarkGroup::name() const noexcept -> const BenchmarkGroupName& {
    return name_;
}

void BenchmarkGroup::add(std::shared_ptr<IBenchmarkCase> bench_case) {
    if (bench_case->info().group_name() != name_) {
        throw StatBenchException(
            fmt::format("Different name of benchmark group to add (Expected: "
                        "{}, Actual: {}).",
                name_, bench_case->info().group_name()));
    }

    const auto& case_name = bench_case->info().case_name();
    const auto [iter, inserted] = cases_.try_emplace(case_name, bench_case);
    if (!inserted) {
        throw StatBenchException(
            fmt::format("Duplicate benchmark name {}.", bench_case->info()));
    }
}

void BenchmarkGroup::filter_by(const filters::ComposedFilter& filter) {
    for (auto iter = cases_.begin(); iter < cases_.end();) {
        if (filter.check((*iter->second).info())) {
            ++iter;
        } else {
            iter = cases_.erase(iter);
        }
    }
}

auto BenchmarkGroup::cases() const noexcept -> const
    util::OrderedMap<BenchmarkCaseName, std::shared_ptr<IBenchmarkCase>>& {
    return cases_;
}

auto BenchmarkGroup::config() noexcept -> BenchmarkGroupConfig& {
    return config_;
}

auto BenchmarkGroup::config() const noexcept -> const BenchmarkGroupConfig& {
    return config_;
}

}  // namespace bench_impl
}  // namespace stat_bench
