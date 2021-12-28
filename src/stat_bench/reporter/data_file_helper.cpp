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
 * \brief Definition of functions to help output of data files.
 */
#include "stat_bench/reporter/data_file_helper.h"

namespace stat_bench {
namespace reporter {
namespace data_file_spec {

auto convert(const param::ParameterDict& params)
    -> std::unordered_map<std::string, std::string> {
    return params.as_string_dict();
}

auto convert(const stat::Statistics& stat) -> StatData {
    return StatData{stat.mean(), stat.max(), stat.min(), stat.variance(),
        stat.standard_deviation()};
}

auto convert(const std::vector<std::vector<clock::Duration>>& durations,
    const stat::Statistics& durations_stat) -> DurationData {
    std::vector<std::vector<double>> values;
    values.reserve(durations.size());
    for (const auto& durations_per_thread : durations) {
        values.emplace_back();
        auto& values_per_thread = values.back();
        values_per_thread.reserve(durations_per_thread.size());
        for (const auto& duration : durations_per_thread) {
            values_per_thread.push_back(duration.seconds());
        }
    }
    return DurationData{convert(durations_stat), std::move(values)};
}

auto convert(const std::shared_ptr<stat::CustomStatOutput>& stat_output,
    const stat::Statistics& stat, std::size_t samples) -> CustomStatOutputData {
    std::vector<std::vector<double>> data;
    for (auto iter = stat.unsorted_samples().begin();
         iter < stat.unsorted_samples().end();
         iter += static_cast<std::ptrdiff_t>(samples)) {
        auto last = iter + static_cast<std::ptrdiff_t>(samples);
        if (last > stat.unsorted_samples().end()) {
            last = stat.unsorted_samples().end();
        }
        data.emplace_back(iter, last);
    }
    return CustomStatOutputData{
        stat_output->name(), convert(stat), std::move(data)};
}

auto convert(
    const std::vector<std::shared_ptr<stat::CustomStatOutput>>& stat_outputs,
    const std::vector<stat::Statistics>& stats, std::size_t samples)
    -> std::vector<CustomStatOutputData> {
    std::vector<CustomStatOutputData> data;
    data.reserve(stat_outputs.size());
    for (std::size_t i = 0; i < stat_outputs.size(); ++i) {
        data.push_back(convert(stat_outputs.at(i), stats.at(i), samples));
    }
    return data;
}

auto convert(const std::vector<std::pair<std::string, double>>& outputs)
    -> std::vector<CustomOutputData> {
    std::vector<CustomOutputData> data;
    data.reserve(outputs.size());
    for (const auto& output : outputs) {
        data.push_back(CustomOutputData{output.first, output.second});
    }
    return data;
}

auto convert(const measurer::Measurement& measurement) -> MeasurementData {
    return MeasurementData{measurement.case_info().group_name(),
        measurement.case_info().case_name(),
        convert(measurement.cond().params()), measurement.measurer_name(),
        measurement.iterations(), measurement.samples(),
        convert(measurement.durations(), measurement.durations_stat()),
        convert(measurement.custom_stat_outputs(), measurement.custom_stat(),
            measurement.samples()),
        convert(measurement.custom_outputs())};
}

}  // namespace data_file_spec
}  // namespace reporter
}  // namespace stat_bench
