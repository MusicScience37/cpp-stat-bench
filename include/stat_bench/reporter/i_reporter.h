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
 * \brief Definition of IReporter class.
 */
#pragma once

#include <exception>

#include "stat_bench/bench_impl/benchmark_group_config.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/clock/system_time_point.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurement_type.h"

namespace stat_bench::reporter {

/*!
 * \brief Interface of reporters.
 */
class IReporter {
public:
    /*!
     * \brief Start an experiment.
     *
     * \param[in] time_stamp Time stamp.
     */
    virtual void experiment_starts(
        const clock::SystemTimePoint& time_stamp) = 0;

    /*!
     * \brief Finished an experiment.
     *
     * \param[in] time_stamp Time stamp.
     */
    virtual void experiment_finished(
        const clock::SystemTimePoint& time_stamp) = 0;

    /*!
     * \brief Start a group of benchmarks.
     *
     * \param[in] name Group name.
     * \param[in] config Configuration.
     */
    virtual void group_starts(const BenchmarkGroupName& name,
        const bench_impl::BenchmarkGroupConfig& config) = 0;

    /*!
     * \brief Finished a group of benchmarks.
     *
     * \param[in] name Group name.
     */
    virtual void group_finished(const BenchmarkGroupName& name) = 0;

    /*!
     * \brief Start a measurement with a type.
     *
     * \param[in] type Measurement type.
     */
    virtual void measurement_type_starts(
        const measurer::MeasurementType& type) = 0;

    /*!
     * \brief Finished a measurement with a type.
     *
     * \param[in] type Measurement type.
     */
    virtual void measurement_type_finished(
        const measurer::MeasurementType& type) = 0;

    /*!
     * \brief Start a case of a benchmark.
     *
     * \param[in] case_info Information.
     */
    virtual void case_starts(const BenchmarkFullName& case_info) = 0;

    /*!
     * \brief Finished a case of a benchmark.
     *
     * \param[in] case_info Information.
     */
    virtual void case_finished(const BenchmarkFullName& case_info) = 0;

    /*!
     * \brief Successfully finished a measurement.
     *
     * \param[in] measurement Measurement.
     */
    virtual void measurement_succeeded(
        const measurer::Measurement& measurement) = 0;

    /*!
     * \brief Failed a measurement.
     *
     * \param[in] case_info Information of the case.
     * \param[in] cond Condition.
     * \param[in] error Error.
     */
    virtual void measurement_failed(const BenchmarkFullName& case_info,
        const BenchmarkCondition& cond, const std::exception_ptr& error) = 0;

    IReporter(const IReporter&) = delete;
    IReporter(IReporter&&) = delete;
    auto operator=(const IReporter&) -> IReporter& = delete;
    auto operator=(IReporter&&) -> IReporter& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~IReporter() = default;

protected:
    /*!
     * \brief Constructor.
     */
    IReporter() = default;
};

}  // namespace stat_bench::reporter
