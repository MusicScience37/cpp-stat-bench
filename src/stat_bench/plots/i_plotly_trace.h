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
 * \brief Definition of IPlotlyTrace class.
 */
#pragma once

#include <utility>

#include <nlohmann/json.hpp>

#include "stat_bench/plots/i_plotter.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of interface of traces in plotly.
 */
class IPlotlyTrace : public ITrace {
public:
    /*!
     * \brief Get data of the trace.
     *
     * \return Data of the trace.
     */
    virtual auto data() -> const nlohmann::json& = 0;

    /*!
     * \brief Get the range of y-axis.
     *
     * \return Minimum and maximum values of y-axis.
     */
    virtual auto y_range() -> std::pair<double, double> = 0;

    /*!
     * \brief Check whether x values are set.
     *
     * \retval true X values are set.
     * \retval false X values are not set.
     */
    virtual auto has_x() -> bool = 0;

    /*!
     * \brief Constructor.
     */
    IPlotlyTrace() = default;

    IPlotlyTrace(const IPlotlyTrace&) = delete;
    IPlotlyTrace(IPlotlyTrace&&) = delete;
    auto operator=(const IPlotlyTrace&) -> IPlotlyTrace& = delete;
    auto operator=(IPlotlyTrace&&) -> IPlotlyTrace& = delete;

    /*!
     * \brief Destructor.
     */
    ~IPlotlyTrace() override = default;
};

}  // namespace plots
}  // namespace stat_bench
