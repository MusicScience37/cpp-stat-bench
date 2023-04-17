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
 * \brief Implementation of MsgPackReporter class.
 */
#include "stat_bench/reporter/msgpack_reporter.h"

#include <fstream>
#include <ios>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "stat_bench/reporter/data_file_helper.h"
#include "stat_bench/reporter/json_data_file_helper.h"  // IWYU pragma: keep
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/prepare_directory.h"

namespace stat_bench {
namespace reporter {

MsgPackReporter::MsgPackReporter(std::string file_path)
    : file_path_(std::move(file_path)) {}

void MsgPackReporter::experiment_starts(
    const clock::SystemTimePoint& time_stamp) {
    data_.started_at = fmt::format(FMT_STRING("{}"), time_stamp);
}

void MsgPackReporter::experiment_finished(
    const clock::SystemTimePoint& time_stamp) {
    data_.finished_at = fmt::format(FMT_STRING("{}"), time_stamp);

    util::prepare_directory_for(file_path_);
    std::ofstream stream{
        file_path_, std::ios_base::out | std::ios_base::binary};
    if (!stream) {
        throw StatBenchException(
            fmt::format(FMT_STRING("Failed to open {}."), file_path_));
    }

    nlohmann::json::to_msgpack(nlohmann::json(data_), stream);
}

void MsgPackReporter::measurer_starts(const std::string& /*name*/) {
    // no operation
}

void MsgPackReporter::measurer_finished(const std::string& /*name*/) {
    // no operation
}

void MsgPackReporter::group_starts(const std::string& /*name*/) {
    // no operation
}

void MsgPackReporter::group_finished(const std::string& /*name*/) {
    // no operation
}

void MsgPackReporter::case_starts(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void MsgPackReporter::case_finished(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void MsgPackReporter::measurement_succeeded(
    const measurer::Measurement& measurement) {
    data_.measurements.push_back(data_file_spec::convert(measurement));
}

void MsgPackReporter::measurement_failed(const BenchmarkFullName& case_info,
    const BenchmarkCondition& cond, const std::exception_ptr& error) {
    // no operation
}

}  // namespace reporter
}  // namespace stat_bench
