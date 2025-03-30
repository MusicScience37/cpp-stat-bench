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
 * \brief Definition of LineTrace class.
 */
#pragma once

#include <string_view>
#include <vector>

#include <plotly_plotter/traces/scatter.h>

#include "plotly_trace_common.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of traces of line plots.
 */
class LineTrace final
    : public PlotlyTraceCommon<plotly_plotter::traces::scatter> {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] trace Trace.
     */
    explicit LineTrace(const plotly_plotter::traces::scatter& trace)
        : PlotlyTraceCommon(trace) {
        trace_.mode("lines");
    }

    LineTrace(const LineTrace&) = delete;
    LineTrace(LineTrace&&) = delete;
    auto operator=(const LineTrace&) -> LineTrace& = delete;
    auto operator=(LineTrace&&) -> LineTrace& = delete;

    /*!
     * \brief Destructor.
     */
    ~LineTrace() override = default;

    //! \copydoc stat_bench::plots::ITrace::x_error
    auto x_error(const std::vector<double>& x_error) -> ITrace* override {
        trace_.error_x().type("data");
        trace_.error_x().array(x_error);
        trace_.error_x().visible(true);
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::y_error
    auto y_error(const std::vector<double>& y_error) -> ITrace* override {
        trace_.error_y().type("data");
        trace_.error_y().array(y_error);
        trace_.error_y().visible(true);
        return this;
    }
};

}  // namespace plots
}  // namespace stat_bench
