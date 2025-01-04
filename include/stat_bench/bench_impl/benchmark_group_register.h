/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
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

#include "stat_bench/bench_impl/benchmark_group.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/util/string_view.h"

namespace stat_bench {
namespace bench_impl {

/*!
 * \brief Class to register benchmark groups.
 */
class BenchmarkGroupRegister {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] name Name of the group.
     */
    explicit BenchmarkGroupRegister(const BenchmarkGroupName& name) noexcept;

    /*!
     * \brief Add a plot of processing time with respect to a parameter to the
     * group.
     *
     * \param[in] parameter_name Parameter name.
     * \return Reference to this object.
     */
    auto add_parameter_to_time_plot(util::StringView parameter_name) noexcept
        -> BenchmarkGroupRegister&;

    /*!
     * \brief Add a plot of processing time with respect to a parameter in the
     * log scale to the group.
     *
     * \param[in] parameter_name Parameter name.
     * \return Reference to this object.
     */
    auto add_parameter_to_time_plot_log(
        util::StringView parameter_name) noexcept -> BenchmarkGroupRegister&;

private:
    //! Group.
    BenchmarkGroup* group_{nullptr};
};

}  // namespace bench_impl
}  // namespace stat_bench
