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
 * \brief Definition of ViolinTrace class.
 */
#pragma once

#include <nlohmann/json.hpp>

#include "plotly_trace_common.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of traces of violin plots.
 */
class ViolinTrace final : public PlotlyTraceCommon {
public:
    /*!
     * \brief Constructor.
     */
    ViolinTrace() {
        trace_ = nlohmann::json::object();
        trace_["type"] = "violin";
        trace_["box"]["visible"] = true;
        trace_["meanline"]["visible"] = true;
        trace_["points"] = "outliers";
    }

    ViolinTrace(const ViolinTrace&) = delete;
    ViolinTrace(ViolinTrace&&) = delete;
    auto operator=(const ViolinTrace&) -> ViolinTrace& = delete;
    auto operator=(ViolinTrace&&) -> ViolinTrace& = delete;

    /*!
     * \brief Destructor.
     */
    ~ViolinTrace() override = default;

    //! \copydoc stat_bench::plots::ITrace::name
    auto name(const util::Utf8String& name) -> ITrace* override {
        PlotlyTraceCommon::name(name);
        trace_["legendgroup"] = name.str();
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::x_error
    auto x_error(const std::vector<double>& x_error) -> ITrace* override {
        // Violin plots do not have x errors.
        (void)x_error;
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::y_error
    auto y_error(const std::vector<double>& y_error) -> ITrace* override {
        // Violin plots do not have y errors.
        (void)y_error;
        return this;
    }
};

}  // namespace plots
}  // namespace stat_bench
