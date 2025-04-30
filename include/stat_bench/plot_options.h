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
 * \brief Definition of PlotOptions class.
 */
#pragma once

#include "stat_bench/plot_option.h"
#include "stat_bench/util/string_view.h"

namespace stat_bench {

/*!
 * \brief Class of options for plots.
 */
class PlotOptions {
public:
    /*!
     * \brief Constructor.
     */
    PlotOptions() noexcept;

    /*!
     * \brief Constructor.
     *
     * \param[in] option Option.
     *
     * \deprecated This function exists for backward compatibility and will be
     * removed in the future.
     */
    PlotOptions(PlotOption::Value option) noexcept;  // NOLINT

    /*!
     * \brief Set whether to plot parameters in the log scale.
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto log_parameter(bool value) noexcept -> PlotOptions&;

    /*!
     * \brief Set whether to plot custom outputs in the log scale.
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto log_output(bool value) noexcept -> PlotOptions&;

    /*!
     * \brief Set parameter name used for columns of subplots.
     *
     * \param[in] value Value. (A string literal.)
     * \return This object.
     *
     * \note This function is assumed to be used with a string literal,
     * and hold only the pointer to the string literal.
     */
    auto subplot_column_parameter_name(const util::StringView& value) noexcept
        -> PlotOptions&;

    /*!
     * \brief Set parameter name used for rows of subplots.
     *
     * \param[in] value Value. (A string literal.)
     * \return This object.
     *
     * \note This function is assumed to be used with a string literal,
     * and hold only the pointer to the string literal.
     */
    auto subplot_row_parameter_name(const util::StringView& value) noexcept
        -> PlotOptions&;

    /*!
     * \brief Get whether to plot parameters in the log scale.
     *
     * \return Whether to plot parameters in the log scale.
     */
    [[nodiscard]] auto log_parameter() const noexcept -> bool;

    /*!
     * \brief Get whether to plot custom outputs in the log scale.
     *
     * \return Whether to plot custom outputs in the log scale.
     */
    [[nodiscard]] auto log_output() const noexcept -> bool;

    /*!
     * \brief Get parameter name used for columns of subplots.
     *
     * \return Parameter name used for columns of subplots.
     */
    [[nodiscard]] auto subplot_column_parameter_name() const noexcept
        -> util::StringView;

    /*!
     * \brief Get parameter name used for rows of subplots.
     *
     * \return Parameter name used for rows of subplots.
     */
    [[nodiscard]] auto subplot_row_parameter_name() const noexcept
        -> util::StringView;

private:
    //! Whether to plot parameters in the log scale.
    bool log_parameter_;

    //! Whether to plot custom outputs in the log scale.
    bool log_output_;

    //! Parameter name used for columns of subplots. (Empty for no columns.)
    util::StringView subplot_column_parameter_name_;

    //! Parameter name used for rows of subplots. (Empty for no rows.)
    util::StringView subplot_row_parameter_name_;
};

}  // namespace stat_bench
