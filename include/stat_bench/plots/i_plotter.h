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

#include <memory>
#include <string>
#include <vector>

#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of interface of figures.
 */
class IFigure {
public:
    /*!
     * \brief Add a line to the figure.
     *
     * \param[in] x X values.
     * \param[in] y Y values.
     * \param[in] name Name of the line.
     */
    virtual void add_line(const std::vector<double>& x,
        const std::vector<double>& y, const util::Utf8String& name) = 0;

    /*!
     * \brief Add a line to the figure with sequential numbers as x values.
     *
     * \param[in] y Y values.
     * \param[in] name Name of the line.
     */
    virtual void add_line_with_sequential_number(
        const std::vector<double>& y, const util::Utf8String& name) = 0;

    /*!
     * \brief Add a violin plot to the figure.
     *
     * \param[in] y Y values.
     * \param[in] name Name of the violin plot.
     */
    virtual void add_violin(
        const std::vector<double>& y, const util::Utf8String& name) = 0;

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
     * \brief Set the range of the y-axis for log scale.
     */
    virtual void set_y_range_for_log() = 0;

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
