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
 * \brief Definition of BenchmarkGroup class.
 */
#pragma once

#include <memory>

#include "stat_bench/bench_impl/benchmark_group_config.h"
#include "stat_bench/bench_impl/i_benchmark_case.h"
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/filters/composed_filter.h"
#include "stat_bench/util/ordered_map.h"

namespace stat_bench::bench_impl {

/*!
 * \brief Class of groups of cases in benchmarks.
 */
class BenchmarkGroup {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] name Name.
     */
    explicit BenchmarkGroup(BenchmarkGroupName name);

    /*!
     * \brief Get the group name.
     *
     * \return Group name.
     */
    [[nodiscard]] auto name() const noexcept -> const BenchmarkGroupName&;

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
     * \brief Get cases.
     *
     * \return Cases.
     */
    [[nodiscard]] auto cases() const noexcept -> const
        util::OrderedMap<BenchmarkCaseName, std::shared_ptr<IBenchmarkCase>>&;

    /*!
     * \brief Get the configuration.
     *
     * \return Configuration.
     */
    [[nodiscard]] auto config() noexcept -> BenchmarkGroupConfig&;

    /*!
     * \brief Get the configuration.
     *
     * \return Configuration.
     */
    [[nodiscard]] auto config() const noexcept -> const BenchmarkGroupConfig&;

private:
    //! Name.
    BenchmarkGroupName name_;

    //! Cases.
    util::OrderedMap<BenchmarkCaseName, std::shared_ptr<IBenchmarkCase>>
        cases_{};

    //! Configuration.
    BenchmarkGroupConfig config_{};
};

}  // namespace stat_bench::bench_impl
