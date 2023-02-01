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
 * \brief Definition of BenchmarkCaseRegistry class.
 */
#pragma once

#include <memory>
#include <vector>

#include "stat_bench/bench_impl/benchmark_group.h"
#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/filters/composed_filter.h"

namespace stat_bench {
namespace bench_impl {

/*!
 * \brief Class of registry of cases of benchmarks.
 */
class BenchmarkCaseRegistry {
public:
    /*!
     * \brief Constructor.
     */
    BenchmarkCaseRegistry() = default;

    /*!
     * \brief Add a case.
     *
     * \param[in] bench_case Case.
     */
    void add(std::shared_ptr<IBenchmarkCase> bench_case);

    /*!
     * \brief Filter.
     *
     * \param[in] filter Filter.
     */
    void filter_by(const filters::ComposedFilter& filter);

    /*!
     * \brief Get benchmarks.
     *
     * \return Benchmarks per group.
     */
    [[nodiscard]] auto benchmarks() const noexcept
        -> const std::vector<BenchmarkGroup>&;

    /*!
     * \brief Get an instance of the registry.
     *
     * \return Reference to the instance.
     */
    [[nodiscard]] static auto instance() -> BenchmarkCaseRegistry&;

private:
    //! Groups.
    std::vector<BenchmarkGroup> groups_{};
};

}  // namespace bench_impl
}  // namespace stat_bench
