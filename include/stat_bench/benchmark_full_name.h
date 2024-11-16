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
 * \brief Definition of BenchmarkFullName class.
 */
#pragma once

#include <string>
#include <utility>

#include <fmt/core.h>
#include <fmt/format.h>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_group_name.h"

namespace stat_bench {

/*!
 * \brief Class of information of cases in benchmarks.
 */
class BenchmarkFullName {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] group_name Name of the group of cases.
     * \param[in] case_name Name of the case in the benchmark.
     */
    BenchmarkFullName(
        BenchmarkGroupName group_name, BenchmarkCaseName case_name) noexcept
        : group_name_(std::move(group_name)),
          case_name_(std::move(case_name)) {}

    /*!
     * \brief Get the name of the group of cases.
     *
     * \return Name of the group of cases.
     */
    [[nodiscard]] auto group_name() const noexcept
        -> const BenchmarkGroupName& {
        return group_name_;
    }

    /*!
     * \brief Get the name of the case in the benchmark.
     *
     * \return Name of the case in the benchmark.
     */
    [[nodiscard]] auto case_name() const noexcept -> const BenchmarkCaseName& {
        return case_name_;
    }

private:
    //! Name of the group of cases.
    BenchmarkGroupName group_name_;

    //! Name of the case in the benchmark.
    BenchmarkCaseName case_name_;
};

}  // namespace stat_bench

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for
 * stat_bench::BenchmarkFullName.
 */
template <>
struct formatter<stat_bench::BenchmarkFullName>
    : public formatter<std::string> {
    /*!
     * \brief Format.
     *
     * \tparam FormatContext Type of the context.
     * \param[in] val Value.
     * \param[in] context Context.
     * \return Output iterator after formatting.
     */
    template <typename FormatContext>
    auto format(const stat_bench::BenchmarkFullName& val,
        FormatContext& context) const -> decltype(context.out()) {
        return formatter<std::string>::format(
            fmt::format("{}/{}", val.group_name(), val.case_name()), context);
    }
};

}  // namespace fmt
