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

#include <plotly_plotter/json_converter_decl.h>
#include <plotly_plotter/json_value.h>

#include "i_plotly_trace.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/util/utf8_string.h"

namespace plotly_plotter {

/*!
 * \brief Specialization of json_converter class for
 * stat_bench::param::ParameterValueVariant.
 */
template <>
class json_converter<stat_bench::param::ParameterValueVariant> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(
        const stat_bench::param::ParameterValueVariant& from, json_value& to) {
        std::visit([&to](const auto& value) { to = value; }, from);
    }
};

/*!
 * \brief Specialization of json_converter class for
 * stat_bench::util::Utf8String.
 */
template <>
class json_converter<stat_bench::util::Utf8String> {
public:
    /*!
     * \brief Convert an object to a JSON value.
     *
     * \param[in] from Object to convert from.
     * \param[out] to JSON value to convert to.
     */
    static void to_json(
        const stat_bench::util::Utf8String& from, json_value& to) {
        to = from.str();
    }
};

}  // namespace plotly_plotter

namespace stat_bench {
namespace plots {

/*!
 * \brief Class to implement some common functions of traces in plotly.
 *
 * \tparam Trace Type of the trace.
 */
template <typename Trace>
class PlotlyTraceCommon : public IPlotlyTrace {
public:
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
        trace_.name(name.str());
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::x
    auto x(const std::vector<double>& x) -> ITrace* override {
        trace_.x(x);
        has_x_ = true;
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::x
    auto x(const std::vector<param::ParameterValueVariant>& x)
        -> ITrace* override {
        trace_.x(x);
        has_x_ = true;
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::generate_sequential_number_for_x
    auto generate_sequential_number_for_x(std::size_t size)
        -> ITrace* override {
        std::vector<std::size_t> x;
        x.reserve(size);
        for (std::size_t i = 0; i < size; ++i) {
            x.push_back(i + 1U);
        }
        trace_.x(x);
        has_x_ = true;
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::y
    auto y(const std::vector<double>& y) -> ITrace* override {
        trace_.y(y);
        for (const auto& value : y) {
            // min_y and max_y are used in log function,
            // so zeros must be ignored.
            if (value <= 0.0) {
                continue;
            }
            min_y_ = std::min(min_y_, value);
            max_y_ = std::max(max_y_, value);
        }
        return this;
    }

    //! \copydoc stat_bench::plots::ITrace::text
    auto text(const std::vector<util::Utf8String>& text) -> ITrace* override {
        trace_.text(text);
        return this;
    }

    //! \copydoc stat_bench::plots::IPlotlyTrace::y_range
    auto y_range() -> std::pair<double, double> override {
        return std::make_pair(min_y_, max_y_);
    }

    //! \copydoc stat_bench::plots::IPlotlyTrace::has_x
    auto has_x() -> bool override { return has_x_; }

protected:
    /*!
     * \brief Constructor.
     *
     * \param[in] trace Trace.
     */
    explicit PlotlyTraceCommon(const Trace& trace) : trace_(trace) {}

    //! Trace.
    Trace trace_;

private:
    //! Minimum value of y-axis.
    double min_y_{std::numeric_limits<double>::max()};

    //! Maximum value of y-axis.
    double max_y_{std::numeric_limits<double>::min()};

    //! Whether x values are set.
    bool has_x_{false};
};

}  // namespace plots
}  // namespace stat_bench
