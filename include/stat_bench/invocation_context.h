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
 * \brief Definition of InvocationContext class.
 */
#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "stat_bench/bench_impl/threadable_invoker.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/stat/custom_stat_output.h"

namespace stat_bench {

/*!
 * \brief Class of context of invocations of benchmarks.
 */
class InvocationContext {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] cond Condition.
     * \param[in] iterations Number of iterations.
     * \param[in] samples Number of samples (including warming up).
     * \param[in] warming_up_samples Number of samples for warming up.
     */
    InvocationContext(BenchmarkCondition cond, std::size_t iterations,
        std::size_t samples, std::size_t warming_up_samples)
        : cond_(std::move(cond)),
          iterations_(iterations),
          samples_(samples),
          warming_up_samples_(warming_up_samples) {}

    InvocationContext(const InvocationContext&) = delete;
    InvocationContext(InvocationContext&&) = delete;
    auto operator=(const InvocationContext&) = delete;
    auto operator=(InvocationContext&&) = delete;

    /*!
     * \brief Destructor.
     */
    ~InvocationContext() = default;

    /*!
     * \brief Get the number of threads.
     *
     * \return Number of threads.
     */
    [[nodiscard]] auto threads() const noexcept -> std::size_t {
        return cond_.threads();
    }

    /*!
     * \brief Get the number of iterations.
     *
     * \return Number of iterations.
     */
    [[nodiscard]] auto iterations() const noexcept -> std::size_t {
        return iterations_;
    }

    /*!
     * \brief Get the number of samples.
     *
     * \return Number of samples.
     */
    [[nodiscard]] auto samples() const noexcept -> std::size_t {
        return samples_;
    }

    /*!
     * \brief Get a parameter.
     *
     * \tparam T Type of the parameter value.
     * \param[in] param_name Parameter name.
     * \return Parameter value.
     */
    template <typename T>
    [[nodiscard]] auto get_param(const param::ParameterName& param_name) const
        -> const T& {
        return cond_.params().get<T>(param_name);
    }

    /*!
     * \brief Get a parameter.
     *
     * \tparam T Type of the parameter value.
     * \param[in] param_name Parameter name.
     * \return Parameter value.
     */
    template <typename T>
    [[nodiscard]] auto get_param(std::string param_name) const -> const T& {
        return get_param<T>(param::ParameterName(std::move(param_name)));
    }

    /*!
     * \brief Add a custom output with statistics.
     *
     * \param[in] name Name.
     * \param[in] analysis_type Type of analysis.
     * \return Object to add output values.
     */
    [[nodiscard]] auto add_custom_stat(const std::string& name,
        stat::CustomOutputAnalysisType analysis_type =
            stat::CustomOutputAnalysisType::mean)
        -> std::shared_ptr<stat::CustomStatOutput> {
        auto out =
            std::make_shared<stat::CustomStatOutput>(name, cond_.threads(),
                samples_, warming_up_samples_, iterations_, analysis_type);
        custom_stat_outputs_.push_back(out);
        return out;
    }

    /*!
     * \brief Add a custom output without statistics.
     *
     * \param[in] name Name.
     * \param[in] value Output value.
     */
    void add_custom_output(const std::string& name, double value) {
        custom_outputs_.emplace_back(name, value);
    }

    /*!
     * \brief Measure time.
     *
     * \tparam Func Type of function.
     * \param[in] func Function.
     */
    template <typename Func>
    void measure(const Func& func) {
        durations_ = bench_impl::ThreadableInvoker(
            cond_.threads(), iterations_, samples_, warming_up_samples_)
                         .measure(func);
    }

    /*!
     * \brief Get the measured durations.
     *
     * \note Duration of iterations in each sample is measured per thread.
     *
     * \return Durations.
     */
    [[nodiscard]] auto durations() const noexcept
        -> const std::vector<std::vector<clock::Duration>>& {
        return durations_;
    }

    /*!
     * \brief Get the custom outputs with statistics.
     *
     * \return Custom outputs with statistics.
     */
    [[nodiscard]] auto custom_stat_outputs() const noexcept
        -> const std::vector<std::shared_ptr<stat::CustomStatOutput>>& {
        return custom_stat_outputs_;
    }

    /*!
     * \brief Get the custom outputs without statistics.
     *
     * \return Custom outputs without statistics.
     */
    [[nodiscard]] auto custom_outputs() const noexcept
        -> const std::vector<std::pair<std::string, double>>& {
        return custom_outputs_;
    }

private:
    //! Condition.
    BenchmarkCondition cond_;

    //! Number of iterations.
    std::size_t iterations_;

    //! Number of samples (including warming up).
    std::size_t samples_;

    //! Number of samples for warming up.
    std::size_t warming_up_samples_;

    //! Measured durations.
    std::vector<std::vector<clock::Duration>> durations_{};

    //! Custom outputs with statistics.
    std::vector<std::shared_ptr<stat::CustomStatOutput>> custom_stat_outputs_{};

    //! Custom outputs without statistics.
    std::vector<std::pair<std::string, double>> custom_outputs_{};
};

}  // namespace stat_bench
