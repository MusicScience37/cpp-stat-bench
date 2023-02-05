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
 * \brief Definition of FixtureBase class.
 */
#pragma once

#include <cstddef>
#include <memory>
#include <string>

#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/current_invocation_context.h"
#include "stat_bench/invocation_context.h"
#include "stat_bench/param/parameter_config.h"
#include "stat_bench/param/parameter_value_vector.h"

namespace stat_bench {

/*!
 * \brief Base class of fixtures.
 */
class FixtureBase : public bench_impl::IBenchmarkCase {
public:
    /*!
     * \name Virtual functions implemented in fixture classes.
     */
    ///@{

    /*!
     * \brief Setup before running actual process.
     *
     * \note This can be implemented in fixtures to perform common
     * initialization process.
     *
     * \param[in] context Context.
     */
    virtual void setup(InvocationContext& context) {
        // no operation in default implementation
    }

    /*!
     * \brief Tear down after running actual process.
     *
     * \note This can be implemented in fixtures to perform common
     * finalization process.
     * \note This will be called even when errors occurred in run function.
     *
     * \param[in] context Context.
     */
    virtual void tear_down(InvocationContext& context) {
        // no operation in default implementation
    }

    ///@}

    /*!
     * \name Functions to set parameters.
     */
    ///@{

    /*!
     * \brief Add a parameter.
     *
     * \tparam T Type of parameter values.
     * \param[in] param_name Parameter name.
     * \return Vector of parameter values.
     */
    template <typename T>
    [[nodiscard]] auto add_param(const std::string& param_name)
        -> std::shared_ptr<param::ParameterValueVector<T>> {
        return params_.add<T>(param_name);
    }

    /*!
     * \brief Add a parameter of the number of threads.
     *
     * \return Vector of parameter values.
     */
    auto add_threads_param()
        -> std::shared_ptr<param::ParameterValueVector<std::size_t>> {
        return add_param<std::size_t>("threads");
    }

    ///@}

    /*!
     * \brief Run actual process in each case.
     *
     * \note This will be implemented in each case, so don't implement in
     * fixtures.
     */
    virtual void run() = 0;

    FixtureBase(const FixtureBase&) = delete;
    FixtureBase(FixtureBase&&) = delete;
    auto operator=(const FixtureBase&) -> FixtureBase& = delete;
    auto operator=(FixtureBase&&) -> FixtureBase& = delete;

    /*!
     * \brief Destructor.
     */
    ~FixtureBase() override = default;

protected:
    /*!
     * \brief Constructor.
     */
    FixtureBase() = default;

private:
    //! \copydoc stat_bench::bench_impl::IBenchmarkCase::execute
    void execute() final {
        auto& context = current_invocation_context();
        setup(context);
        try {
            run();
            tear_down(context);
        } catch (...) {
            tear_down(context);
            throw;
        }
    }

    //! \copydoc stat_bench::bench_impl::IBenchmarkCase::params
    auto params() const noexcept -> const param::ParameterConfig& final {
        return params_;
    }

    //! Parameters.
    param::ParameterConfig params_{};
};

}  // namespace stat_bench
