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
 * \brief Definition of constants for labels in plots.
 */
#pragma once

namespace stat_bench {
namespace plots {

/*!
 * \brief Label for case names in plots.
 */
constexpr const char* case_name_label = "Case";

/*!
 * \brief Label for processing time in plots.
 */
constexpr const char* time_label = "Time [s]";

/*!
 * \brief Label for errors of processing time in plots.
 */
constexpr const char* time_error_label = "Standard Error of Time [s]";

/*!
 * \brief Label for sample index in plots.
 */
constexpr const char* sample_index_label = "Sample Index";

/*!
 * \brief Label for cumulative probability in plots.
 */
constexpr const char* cumulative_probability_label = "Cumulative Probability";

}  // namespace plots
}  // namespace stat_bench
