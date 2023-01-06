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
 * \brief Definition of BenchmarkBase class.
 */
#pragma once

#include <memory>

#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/param/parameter_value_vector.h"

namespace stat_bench {
namespace bench_impl {

/*!
 * \brief Base class of benchmarks.
 */
class BenchmarkBase : public IBenchmarkCase {
public:
    BenchmarkBase(const BenchmarkBase&) = delete;
    BenchmarkBase(BenchmarkBase&&) = delete;
    auto operator=(const BenchmarkBase&) -> BenchmarkBase& = delete;
    auto operator=(BenchmarkBase&&) -> BenchmarkBase& = delete;

    /*!
     * \brief Destructor.
     */
    ~BenchmarkBase() override = default;

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

protected:
    /*!
     * \brief Constructor.
     */
    BenchmarkBase() = default;

private:
    //! \copydoc stat_bench::bench_impl::IBenchmarkCase::params
    auto params() const noexcept -> const param::ParameterConfig& final {
        return params_;
    }

    //! Parameters.
    param::ParameterConfig params_{};
};

}  // namespace bench_impl
}  // namespace stat_bench
