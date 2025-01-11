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
 * \brief Definition of IPlotter class.
 */
#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "stat_bench/param/parameter_value.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of interface of traces in figures.
 */
class ITrace {
public:
    /*!
     * \brief Set the name of the trace.
     *
     * \param[in] name Name.
     * \return This object.
     */
    virtual auto name(const util::Utf8String& name) -> ITrace* = 0;

    /*!
     * \brief Set x values.
     *
     * \param[in] x X values.
     * \return This object.
     */
    virtual auto x(const std::vector<double>& x) -> ITrace* = 0;

    /*!
     * \brief Set x values.
     *
     * \param[in] x X values.
     * \return This object.
     */
    virtual auto x(const std::vector<param::ParameterValueVariant>& x)
        -> ITrace* = 0;

    /*!
     * \brief Generate sequential numbers for x values.
     *
     * \param[in] size Number of sequential numbers.
     * \return This object.
     */
    virtual auto generate_sequential_number_for_x(std::size_t size)
        -> ITrace* = 0;

    /*!
     * \brief Set y values.
     *
     * \param[in] y Y values.
     * \return This object.
     */
    virtual auto y(const std::vector<double>& y) -> ITrace* = 0;

    /*!
     * \brief Set the errors of x values.
     *
     * \param[in] x_error Errors of x values.
     * \return This object.
     */
    virtual auto x_error(const std::vector<double>& x_error) -> ITrace* = 0;

    /*!
     * \brief Set the errors of y values.
     *
     * \param[in] y_error Errors of y values.
     * \return This object.
     */
    virtual auto y_error(const std::vector<double>& y_error) -> ITrace* = 0;

    /*!
     * \brief Set the texts.
     *
     * \param[in] text Texts.
     * \return This object.
     */
    virtual auto text(const std::vector<util::Utf8String>& text) -> ITrace* = 0;

    /*!
     * \brief Constructor.
     */
    ITrace() = default;

    ITrace(const ITrace&) = delete;
    ITrace(ITrace&&) = delete;
    auto operator=(const ITrace&) -> ITrace& = delete;
    auto operator=(ITrace&&) -> ITrace& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~ITrace() = default;
};

/*!
 * \brief Class of interface of figures.
 */
class IFigure {
public:
    /*!
     * \brief Add a trace of a line plot to the figure.
     *
     * \return Trace of the line.
     */
    virtual auto add_line_trace() -> std::shared_ptr<ITrace> = 0;

    /*!
     * \brief Add a trace of a violin plot to the figure.
     *
     * \return Trace of the violin plot.
     */
    virtual auto add_violin_trace() -> std::shared_ptr<ITrace> = 0;

    /*!
     * \brief Set the title of the x-axis.
     *
     * \param[in] title Title.
     */
    virtual void set_x_title(const util::Utf8String& title) = 0;

    /*!
     * \brief Set the title of the y-axis.
     *
     * \param[in] title Title.
     */
    virtual void set_y_title(const util::Utf8String& title) = 0;

    /*!
     * \brief Set the x-axis to be log scale.
     */
    virtual void set_log_x() = 0;

    /*!
     * \brief Set the y-axis to be log scale.
     */
    virtual void set_log_y() = 0;

    /*!
     * \brief Write a figure to a file.
     *
     * \param[in] file_path File path.
     */
    virtual void write_to_file(const std::string& file_path) = 0;

    /*!
     * \brief Constructor.
     */
    IFigure() = default;

    IFigure(const IFigure&) = delete;
    IFigure(IFigure&&) = delete;
    auto operator=(const IFigure&) -> IFigure& = delete;
    auto operator=(IFigure&&) -> IFigure& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~IFigure() = default;
};

/*!
 * \brief Class of interface of plotters.
 */
class IPlotter {
public:
    /*!
     * \brief Create a figure.
     *
     * \param[in] title Title of the figure.
     * \return Created figure.
     */
    [[nodiscard]] virtual auto create_figure(const util::Utf8String& title)
        -> std::unique_ptr<IFigure> = 0;

    /*!
     * \brief Constructor.
     */
    IPlotter() = default;

    IPlotter(const IPlotter&) = delete;
    IPlotter(IPlotter&&) = delete;
    auto operator=(const IPlotter&) -> IPlotter& = delete;
    auto operator=(IPlotter&&) -> IPlotter& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~IPlotter() = default;
};

}  // namespace plots
}  // namespace stat_bench
