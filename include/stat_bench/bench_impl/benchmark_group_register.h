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
#include "stat_bench/plot_options.h"
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
     * \brief Add a line plot of processing time with respect to a parameter to
     * the group.
     *
     * \param[in] parameter_name Parameter name.
     * \param[in] options Options for the plot.
     * \return Reference to this object.
     */
    auto add_parameter_to_time_line_plot(util::StringView parameter_name,
        PlotOptions options = PlotOptions()) noexcept
        -> BenchmarkGroupRegister&;

    /*!
     * \brief Add a line plot of processing time with respect to a parameter in
     * the log scale to the group.
     *
     * \param[in] parameter_name Parameter name.
     * \return Reference to this object.
     *
     * \deprecated This function is deprecated in favor of
     * add_parameter_to_time_line_plot() function.
     */
    [[deprecated("Use add_parameter_to_time_line_plot instead.")]] auto
    add_parameter_to_time_line_plot_log(
        util::StringView parameter_name) noexcept -> BenchmarkGroupRegister&;

    /*!
     * \brief Add a violin plot of processing time with respect to a parameter
     * to the group.
     *
     * \param[in] parameter_name Parameter name.
     * \param[in] options Options for the plot.
     * \return Reference to this object.
     */
    auto add_parameter_to_time_violin_plot(util::StringView parameter_name,
        PlotOptions options = PlotOptions()) noexcept
        -> BenchmarkGroupRegister&;

    /*!
     * \brief Add a box plot of processing time with respect to a parameter to
     * the group.
     *
     * \param[in] parameter_name Parameter name.
     * \param[in] options Options for the plot.
     * \return Reference to this object.
     */
    auto add_parameter_to_time_box_plot(util::StringView parameter_name,
        PlotOptions options = PlotOptions()) noexcept
        -> BenchmarkGroupRegister&;

    /*!
     * \brief Add a line plot of a custom output with respect to a parameter to
     * the group.
     *
     * \param[in] parameter_name Parameter name.
     * \param[in] custom_output_name Custom output name.
     * \param[in] options Options for the plot.
     * \return Reference to this object.
     */
    auto add_parameter_to_output_line_plot(util::StringView parameter_name,
        util::StringView custom_output_name,
        PlotOptions options = PlotOptions()) noexcept
        -> BenchmarkGroupRegister&;

    /*!
     * \brief Add a line plot of a custom output with respect to processing time
     * while parameter changes.
     *
     * \param[in] parameter_name Parameter name.
     * \param[in] custom_output_name Custom output name.
     * \param[in] options Options for the plot.
     * \return Reference to this object.
     */
    auto add_time_to_output_by_parameter_line_plot(
        util::StringView parameter_name, util::StringView custom_output_name,
        PlotOptions options = PlotOptions()) noexcept
        -> BenchmarkGroupRegister&;

private:
    //! Group.
    BenchmarkGroup* group_{nullptr};
};

}  // namespace bench_impl
}  // namespace stat_bench
