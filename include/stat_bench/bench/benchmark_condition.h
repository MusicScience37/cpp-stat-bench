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
 * \brief Definition of BenchmarkCondition class.
 */
#pragma once

#include <cstddef>
#include <utility>

#include "stat_bench/param/parameter_dict.h"

namespace stat_bench {
namespace bench {

/*!
 * \brief Class of conditions of benchmarks.
 */
class BenchmarkCondition {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] threads Number of threads.
     * \param[in] params Parameters.
     */
    BenchmarkCondition(std::size_t threads, param::ParameterDict params)
        : threads_(threads), params_(std::move(params)) {}

    /*!
     * \brief Constructor.
     *
     * \param[in] params Parameters.
     */
    explicit BenchmarkCondition(const param::ParameterDict& params)
        : BenchmarkCondition(params.get<std::size_t>("threads"), params) {}

    /*!
     * \brief Get the number of threads.
     *
     * \return Number of threads.
     */
    [[nodiscard]] auto threads() const noexcept -> std::size_t {
        return threads_;
    }

    /*!
     * \brief Get the parameters.
     *
     * \return Parameters.
     */
    [[nodiscard]] auto params() const noexcept -> const param::ParameterDict& {
        return params_;
    }

private:
    //! Number of threads.
    std::size_t threads_;

    //! Parameters.
    param::ParameterDict params_;
};

}  // namespace bench
}  // namespace stat_bench
