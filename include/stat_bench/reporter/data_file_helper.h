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
 * \brief Declaration of functions to help output of data files.
 */
#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "stat_bench/clock/duration.h"
#include "stat_bench/custom_output_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/reporter/data_file_spec.h"
#include "stat_bench/stat/custom_stat_output.h"
#include "stat_bench/stat/statistics.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace reporter {
namespace data_file_spec {

/*!
 * \brief Convert to data for data files.
 *
 * \param[in] params Parameters.
 * \return Converted data.
 */
[[nodiscard]] auto convert(const param::ParameterDict& params)
    -> std::unordered_map<util::Utf8String, util::Utf8String>;

/*!
 * \brief Convert to data for data files.
 *
 * \param[in] stat Statistics.
 * \return Converted data.
 */
[[nodiscard]] auto convert(const stat::Statistics& stat) -> StatData;

/*!
 * \brief Convert to data for data files.
 *
 * \param[in] durations Durations.
 * \param[in] durations_stat Statistics of durations.
 * \return Converted data.
 */
[[nodiscard]] auto convert(
    const std::vector<std::vector<clock::Duration>>& durations,
    const stat::Statistics& durations_stat) -> DurationData;

/*!
 * \brief Convert to data for data files.
 *
 * \param[in] stat_output Custom output with statistics.
 * \param[in] stat Statistics of custom output.
 * \return Converted data.
 */
[[nodiscard]] auto convert(
    const std::shared_ptr<stat::CustomStatOutput>& stat_output,
    const stat::Statistics& stat) -> CustomStatOutputData;

/*!
 * \brief Convert to data for data files.
 *
 * \param[in] stat_outputs Custom outputs with statistics.
 * \param[in] stats Statistics of custom outputs.
 * \return Converted data.
 */
[[nodiscard]] auto convert(
    const std::vector<std::shared_ptr<stat::CustomStatOutput>>& stat_outputs,
    const std::vector<stat::Statistics>& stats)
    -> std::vector<CustomStatOutputData>;

/*!
 * \brief Convert to data for data files.
 *
 * \param[in] outputs Custom outputs without statistics.
 * \return Converted data.
 */
[[nodiscard]] auto convert(
    const std::vector<std::pair<CustomOutputName, double>>& outputs)
    -> std::vector<CustomOutputData>;

/*!
 * \brief Convert to data for data files.
 *
 * \param[in] measurement Measurement.
 * \return Converted data.
 */
[[nodiscard]] auto convert(const measurer::Measurement& measurement)
    -> MeasurementData;

}  // namespace data_file_spec
}  // namespace reporter
}  // namespace stat_bench
