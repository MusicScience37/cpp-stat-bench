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

#include <fmt/core.h>

#include "stat_bench/stat_bench_exception.h"

namespace stat_bench {
namespace bench_impl {

BenchmarkGroup::BenchmarkGroup(std::string name) : name_(std::move(name)) {}

auto BenchmarkGroup::name() const noexcept -> const std::string& {
    return name_;
}

void BenchmarkGroup::add(std::shared_ptr<IBenchmarkCase> bench_case) {
    if (bench_case->info().group_name() != name_) {
        throw StatBenchException(
            fmt::format("Different name of benchmark group to add (Expected: "
                        "{}, Actual: {}).",
                name_, bench_case->info().group_name()));
    }
    const auto iter = std::find_if(cases_.begin(), cases_.end(),
        [&bench_case](const std::shared_ptr<IBenchmarkCase>& elem) {
            return elem->info().case_name() == bench_case->info().case_name();
        });
    if (iter != cases_.end()) {
        throw StatBenchException(
            fmt::format("Duplicate benchmark name {}.", bench_case->info()));
    }

    cases_.push_back(std::move(bench_case));
}

void BenchmarkGroup::filter_by(const filters::ComposedFilter& filter) {
    for (auto iter = cases_.begin(); iter < cases_.end();) {
        if (filter.check((**iter).info())) {
            ++iter;
        } else {
            iter = cases_.erase(iter);
        }
    }
}

auto BenchmarkGroup::cases() const noexcept
    -> const std::vector<std::shared_ptr<IBenchmarkCase>>& {
    return cases_;
}

}  // namespace bench_impl
}  // namespace stat_bench
