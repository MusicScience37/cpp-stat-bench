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

#include <cstddef>

#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"

namespace stat_bench {
namespace reporter {
namespace data_file_spec {

auto convert(const param::ParameterDict& params)
    -> std::unordered_map<std::string, std::string> {
    return params.as_string_dict();
}

auto convert(const stat::Statistics& stat) -> StatData {
    return StatData{static_cast<float>(stat.mean()),
        static_cast<float>(stat.max()), static_cast<float>(stat.min()),
        static_cast<float>(stat.median()), static_cast<float>(stat.variance()),
        static_cast<float>(stat.standard_deviation()),
        static_cast<float>(stat.standard_error())};
}

auto convert(const std::vector<std::vector<clock::Duration>>& durations,
    const stat::Statistics& durations_stat) -> DurationData {
    std::vector<std::vector<float>> values;
    values.reserve(durations.size());
    for (const auto& durations_per_thread : durations) {
        values.emplace_back();
        auto& values_per_thread = values.back();
        values_per_thread.reserve(durations_per_thread.size());
        for (const auto& duration : durations_per_thread) {
            values_per_thread.push_back(static_cast<float>(duration.seconds()));
        }
    }
    return DurationData{convert(durations_stat), std::move(values)};
}

auto convert(const std::shared_ptr<stat::CustomStatOutput>& stat_output,
    const stat::Statistics& stat) -> CustomStatOutputData {
    std::vector<std::vector<float>> data;
    data.reserve(stat_output->data().size());
    for (const auto& vec : stat_output->data()) {
        std::vector<float> vec_copy;
        vec_copy.reserve(vec.size());
        for (const double val : vec) {
            vec_copy.push_back(static_cast<float>(val));
        }
        data.push_back(std::move(vec_copy));
    }
    return CustomStatOutputData{stat_output->name(), convert(stat), data};
}

auto convert(
    const std::vector<std::shared_ptr<stat::CustomStatOutput>>& stat_outputs,
    const std::vector<stat::Statistics>& stats)
    -> std::vector<CustomStatOutputData> {
    std::vector<CustomStatOutputData> data;
    data.reserve(stat_outputs.size());
    for (std::size_t i = 0; i < stat_outputs.size(); ++i) {
        data.push_back(convert(stat_outputs.at(i), stats.at(i)));
    }
    return data;
}

auto convert(const std::vector<std::pair<std::string, double>>& outputs)
    -> std::vector<CustomOutputData> {
    std::vector<CustomOutputData> data;
    data.reserve(outputs.size());
    for (const auto& output : outputs) {
        data.push_back(
            CustomOutputData{output.first, static_cast<float>(output.second)});
    }
    return data;
}

auto convert(const measurer::Measurement& measurement) -> MeasurementData {
    return MeasurementData{measurement.case_info().group_name().str().str(),
        measurement.case_info().case_name().str().str(),
        convert(measurement.cond().params()),
        measurement.measurer_name().str().str(), measurement.iterations(),
        measurement.samples(),
        convert(measurement.durations(), measurement.durations_stat()),
        convert(measurement.custom_stat_outputs(), measurement.custom_stat()),
        convert(measurement.custom_outputs())};
}

}  // namespace data_file_spec
}  // namespace reporter
}  // namespace stat_bench
