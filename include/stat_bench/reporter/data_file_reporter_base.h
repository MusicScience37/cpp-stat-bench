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
 * \brief Definition of DataFileReporterBase class.
 */
#pragma once

#include <string>

#include "stat_bench/reporter/data_file_spec.h"
#include "stat_bench/reporter/i_reporter.h"

namespace stat_bench {
namespace reporter {

/*!
 * \brief Base class to write data files.
 */
class DataFileReporterBase : public IReporter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] file_path File path.
     */
    explicit DataFileReporterBase(std::string file_path);

    /*!
     * \brief Write a data file.
     *
     * \param[in] file_path File path.
     * \param[in] data Data.
     */
    virtual void write_data_file(
        const std::string& file_path, const data_file_spec::RootData& data) = 0;

    //! \copydoc stat_bench::reporter::IReporter::experiment_starts
    void experiment_starts(const clock::SystemTimePoint& time_stamp) final;

    //! \copydoc stat_bench::reporter::IReporter::experiment_finished
    void experiment_finished(const clock::SystemTimePoint& time_stamp) final;

    //! \copydoc stat_bench::reporter::IReporter::group_starts
    void group_starts(const BenchmarkGroupName& name,
        const bench_impl::BenchmarkGroupConfig& config) final;

    //! \copydoc stat_bench::reporter::IReporter::group_finished
    void group_finished(const BenchmarkGroupName& name) final;

    //! \copydoc stat_bench::reporter::IReporter::measurement_type_starts
    void measurement_type_starts(const measurer::MeasurementType& type) final;

    //! \copydoc stat_bench::reporter::IReporter::measurement_type_finished
    void measurement_type_finished(const measurer::MeasurementType& type) final;

    //! \copydoc stat_bench::reporter::IReporter::case_starts
    void case_starts(const BenchmarkFullName& case_info) final;

    //! \copydoc stat_bench::reporter::IReporter::case_finished
    void case_finished(const BenchmarkFullName& case_info) final;

    //! \copydoc stat_bench::reporter::IReporter::measurement_succeeded
    void measurement_succeeded(const measurer::Measurement& measurement) final;

    //! \copydoc stat_bench::reporter::IReporter::measurement_failed
    void measurement_failed(const BenchmarkFullName& case_info,
        const BenchmarkCondition& cond, const std::exception_ptr& error) final;

private:
    //! File path.
    std::string file_path_;

    //! Data.
    data_file_spec::RootData data_{};
};

}  // namespace reporter
}  // namespace stat_bench
