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
 * \brief Implementation of ComposedFilter class.
 */
#include "stat_bench/filters/composed_filter.h"

#include <algorithm>
#include <memory>

#include "stat_bench/filters/glob_filter.h"
#include "stat_bench/filters/regex_filter.h"

namespace stat_bench::filters {

void ComposedFilter::include_with_glob(const std::string& pattern) {
    included_filter_.push_back(std::make_shared<GlobFilter>(pattern));
}

void ComposedFilter::exclude_with_glob(const std::string& pattern) {
    excluded_filter_.push_back(std::make_shared<GlobFilter>(pattern));
}

void ComposedFilter::include_with_regex(const std::string& regex) {
    included_filter_.push_back(std::make_shared<RegexFilter>(regex));
}

void ComposedFilter::exclude_with_regex(const std::string& regex) {
    excluded_filter_.push_back(std::make_shared<RegexFilter>(regex));
}

auto ComposedFilter::check(const BenchmarkFullName& name) const -> bool {
    return (included_filter_.empty() ||
               std::any_of(included_filter_.begin(), included_filter_.end(),
                   [&name](const std::shared_ptr<INameFilter>& filter) {
                       return filter->check(name);
                   })) &&
        std::none_of(excluded_filter_.begin(), excluded_filter_.end(),
            [&name](const std::shared_ptr<INameFilter>& filter) {
                return filter->check(name);
            });
}

}  // namespace stat_bench::filters
