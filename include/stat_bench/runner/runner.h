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

// IWYU pragma: no_include  <stddef.h>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <lyra/cli.hpp>
#include <lyra/lyra.hpp>

#include "stat_bench/bench/benchmark_case_registry.h"
#include "stat_bench/bench/benchmark_condition.h"
#include "stat_bench/bench/i_benchmark_case.h"
#include "stat_bench/measurer/i_measurer.h"
#include "stat_bench/measurer/measurement.h"
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
        bench::BenchmarkCaseRegistry& registry =
            bench::BenchmarkCaseRegistry::instance());

    /*!
     * \brief Constructor.
     *
     * \param[in] registry Registry of benchmarks.
     */
    explicit Runner(bench::BenchmarkCaseRegistry& registry =
                        bench::BenchmarkCaseRegistry::instance());

    Runner(const Runner&) = delete;
    Runner(Runner&&) = delete;
    auto operator=(const Runner&) -> Runner& = delete;
    auto operator=(Runner&&) -> Runner& = delete;

    /*!
     * \brief Destructor.
     */
    ~Runner();

    /*!
     * \brief Add a measurer.
     *
     * \param[in] measurer Measurer.
     */
    void add(std::shared_ptr<measurer::IMeasurer> measurer) {
        measurers_.push_back(std::move(measurer));
    }

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
     * \param[in] measurer Measurer.
     * \param[in] bench_case Case.
     */
    void run_case(const std::shared_ptr<measurer::IMeasurer>& measurer,
        const std::shared_ptr<bench::IBenchmarkCase>& bench_case) const;

    /*!
     * \brief Run a case.
     *
     * \param[in] measurer Measurer.
     * \param[in] bench_case Case.
     * \param[in] cond Condition.
     */
    void run_case_with_condition(
        const std::shared_ptr<measurer::IMeasurer>& measurer,
        const std::shared_ptr<bench::IBenchmarkCase>& bench_case,
        const bench::BenchmarkCondition& cond) const;

    //! Measurers.
    std::vector<std::shared_ptr<measurer::IMeasurer>> measurers_{};

    //! Reporters.
    std::vector<std::shared_ptr<reporter::IReporter>> reporters_{};

    //! Registry.
    bench::BenchmarkCaseRegistry& registry_;
};

}  // namespace runner
}  // namespace stat_bench
