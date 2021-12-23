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
#include <vector>

#include <lyra/lyra.hpp>

#include "stat_bench/bench/benchmark_case_registry.h"
#include "stat_bench/bench/i_benchmark_case.h"
#include "stat_bench/measurer/i_measurer.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/reporter/i_reporter.h"

namespace stat_bench {
namespace runner {

namespace impl {

//! Default number of samples for measurements of processing time.
static constexpr std::size_t default_processing_time_samples = 100;

//! Default number of samples for measurement of mean processing time.
static constexpr std::size_t default_mean_processing_time_samples = 30;

/*!
 * \brief Default minimum duration of a sample for measurement of mean
 * processing time. [sec]
 */
static constexpr double default_min_sample_duration_sec = 0.03;

}  // namespace impl

/*!
 * \brief Class of configurations.
 */
struct Config {
    //! Whether to show help.
    bool show_help{false};

    //! Number of samples for measurements of processing time.
    std::size_t processing_time_samples{impl::default_processing_time_samples};

    //! Number of samples for measurements of mean processing time.
    std::size_t mean_processing_time_samples{
        impl::default_mean_processing_time_samples};

    /*!
     * \brief minimum duration of a sample for measurement of mean processing
     * time. [sec]
     */
    double min_sample_duration_sec{impl::default_min_sample_duration_sec};
};

/*!
 * \brief Class of runners of benchmarks.
 */
class Runner {
public:
    /*!
     * \brief Constructor.
     */
    Runner();

    Runner(const Runner&) = delete;
    Runner(Runner&&) = delete;
    auto operator=(const Runner&) -> Runner& = delete;
    auto operator=(Runner&&) -> Runner& = delete;

    /*!
     * \brief Destructor.
     */
    ~Runner();

    /*!
     * \brief Access to the command line interface definition.
     *
     * \return Reference to the definition.
     */
    [[nodiscard]] auto cli() -> lyra::cli& { return cli_; }

    /*!
     * \brief Parse command line arguments.
     *
     * \param[in] argc Number of arguments.
     * \param[in] argv Arguments.
     */
    void parse_cli(int argc, const char** argv);

    /*!
     * \brief Get the configuration.
     *
     * \return Configuration.
     */
    [[nodiscard]] auto config() -> const Config& { return config_; }

    /*!
     * \brief Initialize.
     */
    void init();

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
    void run() const { run(bench::BenchmarkCaseRegistry::instance()); }

    /*!
     * \brief Run benchmarks.
     *
     * \param[in] registry Registry of benchmarks.
     */
    void run(const bench::BenchmarkCaseRegistry& registry) const;

private:
    /*!
     * \brief Run a case.
     *
     * \param[in] measurer Measurer.
     * \param[in] bench_case Case.
     */
    void run_case(const std::shared_ptr<measurer::IMeasurer>& measurer,
        const std::shared_ptr<bench::IBenchmarkCase>& bench_case) const;

    //! Configurations.
    Config config_{};

    //! Command line interface.
    lyra::cli cli_{};

    //! Measurers.
    std::vector<std::shared_ptr<measurer::IMeasurer>> measurers_{};

    //! Reporters.
    std::vector<std::shared_ptr<reporter::IReporter>> reporters_{};
};

}  // namespace runner
}  // namespace stat_bench
