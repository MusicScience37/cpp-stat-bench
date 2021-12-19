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
 * \brief Definition of BenchmarkCaseInfo class.
 */
#pragma once

#include <memory>

#include <fmt/format.h>

namespace stat_bench {
namespace bench {

/*!
 * \brief Class of information of cases in benchmarks.
 */
class BenchmarkCaseInfo {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] benchmark_name Name of the benchmark.
     * \param[in] case_name Name of the case in the benchmark.
     */
    BenchmarkCaseInfo(
        std::string benchmark_name, std::string case_name) noexcept
        : benchmark_name_(std::move(benchmark_name)),
          case_name_(std::move(case_name)) {}

    /*!
     * \brief Get the name of the benchmark.
     *
     * \return Name of the benchmark.
     */
    [[nodiscard]] auto benchmark_name() const noexcept -> const std::string& {
        return benchmark_name_;
    }

    /*!
     * \brief Get the name of the case in the benchmark.
     *
     * \return Name of the case in the benchmark.
     */
    [[nodiscard]] auto case_name() const noexcept -> const std::string& {
        return case_name_;
    }

private:
    //! Name of the benchmark.
    std::string benchmark_name_;

    //! Name of the case in the benchmark.
    std::string case_name_;
};

}  // namespace bench
}  // namespace stat_bench

namespace fmt {

/*!
 * \brief Implementation of fmt::formatter for
 * stat_bench::bench::BenchmarkCaseInfo.
 */
template <>
struct formatter<stat_bench::bench::BenchmarkCaseInfo>
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
    auto format(const stat_bench::bench::BenchmarkCaseInfo& val,
        FormatContext& context) -> decltype(context.out()) {
        return format_to(
            context.out(), "{}/{}", val.benchmark_name(), val.case_name());
    }
};

}  // namespace fmt
