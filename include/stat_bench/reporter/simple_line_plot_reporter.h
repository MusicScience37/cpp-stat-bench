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
 * \brief Definition of SimpleLinePlotReporter class.
 */
#pragma once

#include <exception>
#include <string>
#include <vector>

#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/system_time_point.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/reporter/i_reporter.h"
#include "stat_bench/reporter/jinja_renderer.h"

namespace stat_bench {
namespace reporter {

/*!
 * \brief Class to generates line plots of results.
 */
class SimpleLinePlotReporter final : public IReporter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] prefix File prefix.
     */
    explicit SimpleLinePlotReporter(std::string prefix);

    //! \copydoc stat_bench::reporter::IReporter::experiment_starts
    void experiment_starts(const clock::SystemTimePoint& time_stamp) override;

    //! \copydoc stat_bench::reporter::IReporter::experiment_finished
    void experiment_finished(const clock::SystemTimePoint& time_stamp) override;

    //! \copydoc stat_bench::reporter::IReporter::measurer_starts
    void measurer_starts(const std::string& name) override;

    //! \copydoc stat_bench::reporter::IReporter::measurer_finished
    void measurer_finished(const std::string& name) override;

    //! \copydoc stat_bench::reporter::IReporter::group_starts
    void group_starts(const std::string& name) override;

    //! \copydoc stat_bench::reporter::IReporter::group_finished
    void group_finished(const std::string& name) override;

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
    //! File prefix.
    std::string prefix_;

    //! Measurer name.
    std::string measurer_name_{};

    //! Measurements.
    std::vector<measurer::Measurement> measurements_{};

    //! Renderer of Jinja templates.
    JinjaRenderer renderer_{};
};

}  // namespace reporter
}  // namespace stat_bench
