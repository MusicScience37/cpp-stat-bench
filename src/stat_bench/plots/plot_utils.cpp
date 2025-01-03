/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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
 * \brief Implementation of utility functions for plots.
 */
#include "stat_bench/plots/plot_utils.h"

#include <fmt/format.h>

namespace stat_bench {
namespace plots {

auto generate_plot_name(const BenchmarkCaseName& case_name,
    const param::ParameterDict& params) -> util::Utf8String {
    if (params.empty()) {
        return case_name.str();
    }
    return util::Utf8String(fmt::format("{} ({})", case_name.str(), params));
}

}  // namespace plots
}  // namespace stat_bench
