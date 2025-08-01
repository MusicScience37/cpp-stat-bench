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
 * \brief Definition of Runner class.
 */
#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "stat_bench/bench_impl/benchmark_case_registry.h"
#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/measurement_config.h"
#include "stat_bench/measurer/measurer.h"
#include "stat_bench/reporter/i_reporter.h"
#include "stat_bench/runner/config.h"

namespace stat_bench {
namespace runner {

/*!
 * \brief Class of runners of benchmarks.
 */
class Runner {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] config Configuration.
     * \param[in] registry Registry of benchmarks.
     */
    explicit Runner(const Config& config,
        bench_impl::BenchmarkCaseRegistry& registry =
            bench_impl::BenchmarkCaseRegistry::instance());

    /*!
     * \brief Constructor.
     *
     * \param[in] registry Registry of benchmarks.
     */
    explicit Runner(bench_impl::BenchmarkCaseRegistry& registry =
                        bench_impl::BenchmarkCaseRegistry::instance())
        : Runner(Config{}, registry) {}

    Runner(const Runner&) = delete;
    Runner(Runner&&) = delete;
    auto operator=(const Runner&) -> Runner& = delete;
    auto operator=(Runner&&) -> Runner& = delete;

    /*!
     * \brief Destructor.
     */
    ~Runner();

    /*!
     * \brief Add a reporter.
     *
     * \param[in] reporter Reporter.
     */
    void add(std::shared_ptr<reporter::IReporter> reporter) {
        reporters_.push_back(std::move(reporter));
    }

    /*!
     * \brief Run benchmarks.
     */
    void run() const;

private:
    /*!
     * \brief Run a case.
     *
     * \param[in] bench_case Case.
     * \param[in] measurement_config Measurement configuration.
     */
    void run_case(const std::shared_ptr<bench_impl::IBenchmarkCase>& bench_case,
        const MeasurementConfig& measurement_config) const;

    /*!
     * \brief Run a case.
     *
     * \param[in] bench_case Case.
     * \param[in] condition Condition.
     * \param[in] measurement_config Measurement configuration.
     */
    void run_case_with_condition(
        const std::shared_ptr<bench_impl::IBenchmarkCase>& bench_case,
        const BenchmarkCondition& condition,
        const MeasurementConfig& measurement_config) const;

    //! Measurer.
    measurer::Measurer measurer_;

    //! Reporters.
    std::vector<std::shared_ptr<reporter::IReporter>> reporters_{};

    //! Registry.
    bench_impl::BenchmarkCaseRegistry& registry_;
};

}  // namespace runner
}  // namespace stat_bench
