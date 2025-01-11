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
 * \brief Definition of PlotlyTraceCommon class.
 */
#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <utility>
#include <variant>
#include <vector>

#include <nlohmann/json.hpp>

#include "i_plotly_trace.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class to implement some common functions of traces in plotly.
 */
class PlotlyTraceCommon : public IPlotlyTrace {
public:
    /*!
     * \brief Constructor.
     */
    PlotlyTraceCommon() = default;

    PlotlyTraceCommon(const PlotlyTraceCommon&) = delete;
    PlotlyTraceCommon(PlotlyTraceCommon&&) = delete;
    auto operator=(const PlotlyTraceCommon&) -> PlotlyTraceCommon& = delete;
    auto operator=(PlotlyTraceCommon&&) -> PlotlyTraceCommon& = delete;

    /*!
     * \brief Destructor.
     */
    ~PlotlyTraceCommon() override = default;

    //! \copydoc stat_bench::plots::ITrace::name
    auto name(const util::Utf8String& name) -> ITrace* override {
        trace_["name"] = name.str();
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::x
    auto x(const std::vector<double>& x) -> ITrace* override {
        trace_["x"] = x;
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::x
    auto x(const std::vector<param::ParameterValueVariant>& x)
        -> ITrace* override {
        auto& x_json = trace_["x"];
        x_json = nlohmann::json::array();
        for (const auto& value : x) {
            std::visit(
                [&x_json](const auto& value) { x_json.push_back(value); },
                value);
        }
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::generate_sequential_number_for_x
    auto generate_sequential_number_for_x(std::size_t size)
        -> ITrace* override {
        trace_["x"] = nlohmann::json::array();
        for (std::size_t i = 0; i < size; ++i) {
            trace_["x"].push_back(i + 1U);
        }
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::y
    auto y(const std::vector<double>& y) -> ITrace* override {
        trace_["y"] = y;
        for (const auto& value : y) {
            min_y_ = std::min(min_y_, value);
            max_y_ = std::max(max_y_, value);
        }
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::text
    auto text(const std::vector<util::Utf8String>& text) -> ITrace* override {
        auto& text_json = trace_["text"];
        text_json = nlohmann::json::array();
        for (const auto& text : text) {
            text_json.push_back(text.str());
        }
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::data
    auto data() -> const nlohmann::json& override { return trace_; }

    //! \copydoc stat_bench::plots::ITrace::y_range
    auto y_range() -> std::pair<double, double> override {
        return std::make_pair(min_y_, max_y_);
    }

protected:
    //! Data of the trace.
    nlohmann::json trace_{nlohmann::json::object()};

private:
    //! Minimum value of y-axis.
    double min_y_{std::numeric_limits<double>::max()};

    //! Maximum value of y-axis.
    double max_y_{std::numeric_limits<double>::min()};
};

}  // namespace plots
}  // namespace stat_bench
