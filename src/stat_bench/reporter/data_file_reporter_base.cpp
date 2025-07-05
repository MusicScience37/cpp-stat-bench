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
 * \brief Implementation of DataFileReporterBase class.
 */
#include "stat_bench/reporter/data_file_reporter_base.h"

#include <utility>
#include <vector>

#include <fmt/format.h>

#include "stat_bench/reporter/data_file_helper.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace reporter {

DataFileReporterBase::DataFileReporterBase(std::string file_path)
    : file_path_(std::move(file_path)) {}

void DataFileReporterBase::experiment_starts(
    const clock::SystemTimePoint& time_stamp) {
    data_.started_at =
        util::Utf8String(fmt::format(FMT_STRING("{}"), time_stamp));
}

void DataFileReporterBase::experiment_finished(
    const clock::SystemTimePoint& time_stamp) {
    data_.finished_at =
        util::Utf8String(fmt::format(FMT_STRING("{}"), time_stamp));

    write_data_file(file_path_, data_);
}

void DataFileReporterBase::measurer_starts(
    const measurer::MeasurementType& /*name*/) {
    // no operation
}

void DataFileReporterBase::measurer_finished(
    const measurer::MeasurementType& /*name*/) {
    // no operation
}

void DataFileReporterBase::group_starts(const BenchmarkGroupName& /*name*/,
    const bench_impl::BenchmarkGroupConfig& /*config*/) {
    // no operation
}

void DataFileReporterBase::group_finished(const BenchmarkGroupName& /*name*/) {
    // no operation
}

void DataFileReporterBase::case_starts(const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void DataFileReporterBase::case_finished(
    const BenchmarkFullName& /*case_info*/) {
    // no operation
}

void DataFileReporterBase::measurement_succeeded(
    const measurer::Measurement& measurement) {
    data_.measurements.push_back(data_file_spec::convert(measurement));
}

void DataFileReporterBase::measurement_failed(
    const BenchmarkFullName& case_info, const BenchmarkCondition& cond,
    const std::exception_ptr& error) {
    // no operation
    (void)case_info;
    (void)cond;
    (void)error;
}

}  // namespace reporter
}  // namespace stat_bench
