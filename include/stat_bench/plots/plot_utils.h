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
 * \brief Declaration of utility functions for plots.
 */
#pragma once

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Generate a name for a plot.
 *
 * \param[in] case_name Benchmark case name.
 * \param[in] params Parameters.
 * \return Name for the plot.
 */
[[nodiscard]] auto generate_plot_name(const BenchmarkCaseName& case_name,
    const param::ParameterDict& params) -> util::Utf8String;

}  // namespace plots
}  // namespace stat_bench
