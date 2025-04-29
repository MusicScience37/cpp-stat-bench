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

namespace stat_bench {

/*!
 * \brief Class of options for plots.
 */
class PlotOptions {
public:
    /*!
     * \brief Constructor.
     */
    PlotOptions();

    /*!
     * \brief Constructor.
     *
     * \param[in] option Option.
     */
    PlotOptions(PlotOption::Value option);  // NOLINT

    /*!
     * \brief Set whether to plot parameters in the log scale.
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto log_parameter(bool value) -> PlotOptions&;

    /*!
     * \brief Set whether to plot custom outputs in the log scale.
     *
     * \param[in] value Value.
     * \return This object.
     */
    auto log_output(bool value) -> PlotOptions&;

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

private:
    //! Whether to plot parameters in the log scale.
    bool log_parameter_;

    //! Whether to plot custom outputs in the log scale.
    bool log_output_;
};

}  // namespace stat_bench
