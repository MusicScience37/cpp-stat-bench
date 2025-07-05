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
 * \brief Definition of PlotReporter class.
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurement_type.h"
#include "stat_bench/plots/i_plot.h"
#include "stat_bench/reporter/i_reporter.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace reporter {

/*!
 * \brief Class to generate plots of measurement results.
 */
class PlotReporter final : public IReporter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] prefix File prefix.
     */
    explicit PlotReporter(std::string prefix);

    //! \copydoc stat_bench::reporter::IReporter::experiment_starts
    void experiment_starts(const clock::SystemTimePoint& time_stamp) override;

    //! \copydoc stat_bench::reporter::IReporter::experiment_finished
    void experiment_finished(const clock::SystemTimePoint& time_stamp) override;

    //! \copydoc stat_bench::reporter::IReporter::group_starts
    void group_starts(const BenchmarkGroupName& name,
        const bench_impl::BenchmarkGroupConfig& config) override;

    //! \copydoc stat_bench::reporter::IReporter::group_finished
    void group_finished(const BenchmarkGroupName& name) override;

    //! \copydoc stat_bench::reporter::IReporter::measurement_type_starts
    void measurement_type_starts(const measurer::MeasurementType& type) final;

    //! \copydoc stat_bench::reporter::IReporter::measurement_type_finished
    void measurement_type_finished(const measurer::MeasurementType& type) final;

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

    //! Group name.
    BenchmarkGroupName group_name_;

    //! Measurement type.
    measurer::MeasurementType measurement_type_;

    //! Measurement type.for file paths.
    util::Utf8String measurement_type_for_file_paths_;

    //! Measurements.
    std::vector<measurer::Measurement> measurements_{};

    //! Builtin plots.
    std::vector<std::shared_ptr<plots::IPlot>> builtin_plots_{};

    //! Plots in groups.
    std::vector<std::shared_ptr<plots::IPlot>> group_plots_{};
};

}  // namespace reporter
}  // namespace stat_bench
