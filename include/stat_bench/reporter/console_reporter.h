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
 * \brief Definition of ConsoleReporter class.
 */
#pragma once

// IWYU pragma: no_include <cwchar>

#include <cstdio>

#include "stat_bench/reporter/i_reporter.h"

namespace stat_bench {
namespace reporter {

/*!
 * \brief Class to report results to consoles.
 */
class ConsoleReporter final : public IReporter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] file File pointer of the console.
     */
    explicit ConsoleReporter(std::FILE* file = stdout);

    //! \copydoc stat_bench::reporter::IReporter::experiment_starts
    void experiment_starts(const clock::SystemTimePoint& time_stamp) override;

    //! \copydoc stat_bench::reporter::IReporter::experiment_finished
    void experiment_finished(const clock::SystemTimePoint& time_stamp) override;

    //! \copydoc stat_bench::reporter::IReporter::measurer_starts
    void measurer_starts(const measurer::MeasurementType& name) override;

    //! \copydoc stat_bench::reporter::IReporter::measurer_finished
    void measurer_finished(const measurer::MeasurementType& name) override;

    //! \copydoc stat_bench::reporter::IReporter::group_starts
    void group_starts(const BenchmarkGroupName& name,
        const bench_impl::BenchmarkGroupConfig& config) override;

    //! \copydoc stat_bench::reporter::IReporter::group_finished
    void group_finished(const BenchmarkGroupName& name) override;

    //! \copydoc stat_bench::reporter::IReporter::case_starts
    void case_starts(const BenchmarkFullName& case_info) override;

    //! \copydoc stat_bench::reporter::IReporter::case_finished
    void case_finished(const BenchmarkFullName& case_info) override;

    //! \copydoc stat_bench::reporter::IReporter::measurement_succeeded
    void measurement_succeeded(
        const measurer::Measurement& measurement) override;

    //! \copydoc stat_bench::reporter::IReporter::measurement_failed
    void measurement_failed(const BenchmarkFullName& case_info,
        const BenchmarkCondition& cond,
        const std::exception_ptr& error) override;

private:
    //! File pointer of the console.
    std::FILE* file_;
};

}  // namespace reporter
}  // namespace stat_bench
