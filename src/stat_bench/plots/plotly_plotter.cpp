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
 * \brief Definition of PlotlyPlotter class.
 */
#include "stat_bench/plots/plotly_plotter.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <plotly_plotter/figure.h>
#include <plotly_plotter/layout.h>
#include <plotly_plotter/write_html.h>

#include "box_trace.h"
#include "i_plotly_trace.h"
#include "line_trace.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/stat_bench_exception.h"
#include "stat_bench/util/prepare_directory.h"
#include "stat_bench/util/utf8_string.h"
#include "violin_trace.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Struct to store data of a figure using plotly.
 */
class PlotlyFigure final : public IFigure {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] title Title of this figure.
     */
    explicit PlotlyFigure(const util::Utf8String& title) {
        figure_.title(title.str());

        figure_.layout().show_legend(true);
    }

    PlotlyFigure(const PlotlyFigure&) = delete;
    PlotlyFigure(PlotlyFigure&&) = delete;
    auto operator=(const PlotlyFigure&) -> PlotlyFigure& = delete;
    auto operator=(PlotlyFigure&&) -> PlotlyFigure& = delete;

    /*!
     * \brief Destructor.
     */
    ~PlotlyFigure() override = default;

    //! \copydoc stat_bench::plots::IFigure::add_line_trace
    [[nodiscard]] auto add_line_trace() -> std::shared_ptr<ITrace> override {
        auto trace = std::make_shared<LineTrace>(figure_.add_scatter());
        traces_.push_back(trace);
        return trace;
    }

    //! \copydoc stat_bench::plots::IFigure::add_violin_trace
    [[nodiscard]] auto add_violin_trace() -> std::shared_ptr<ITrace> override {
        auto trace = std::make_shared<ViolinTrace>(figure_.add_violin());
        traces_.push_back(trace);
        is_violin_ = true;
        return trace;
    }

    //! \copydoc stat_bench::plots::IFigure::add_box_trace
    [[nodiscard]] auto add_box_trace() -> std::shared_ptr<ITrace> override {
        auto trace = std::make_shared<BoxTrace>(figure_.add_box());
        traces_.push_back(trace);
        is_box_ = true;
        return trace;
    }

    //! \copydoc stat_bench::plots::IFigure::set_x_title
    void set_x_title(const util::Utf8String& title) override {
        figure_.layout().xaxis().title().text(title.str());
    }

    //! \copydoc stat_bench::plots::IFigure::set_y_title
    void set_y_title(const util::Utf8String& title) override {
        figure_.layout().yaxis().title().text(title.str());
    }

    //! \copydoc stat_bench::plots::IFigure::set_log_x
    void set_log_x() override { figure_.layout().xaxis().type("log"); }

    //! \copydoc stat_bench::plots::IFigure::set_log_y
    void set_log_y() override {
        figure_.layout().yaxis().type("log");
        is_log_y_ = true;
    }

    //! \copydoc stat_bench::plots::IFigure::write_to_file
    void write_to_file(const std::string& file_path) override {
        if (traces_.empty()) {
            throw StatBenchException("No traces are added to the figure.");
        }

        double min_y = std::numeric_limits<double>::infinity();
        double max_y = -std::numeric_limits<double>::infinity();
        for (const auto& trace : traces_) {
            const auto [trace_min_y, trace_max_y] = trace->y_range();
            min_y = std::min(min_y, trace_min_y);
            max_y = std::max(max_y, trace_max_y);
        }

        if (is_violin_ && is_log_y_) {
            // For this case, spacial treatment is needed to prevent wrong
            // automatic range in plotly library.
            constexpr double margin_in_log = 0.17;
            const double lower_bound_in_log = std::log10(min_y) - margin_in_log;
            const double upper_bound_in_log = std::log10(max_y) + margin_in_log;
            figure_.layout().yaxis().range(
                lower_bound_in_log, upper_bound_in_log);
            figure_.layout().yaxis().constrain("range");
        }
        if (is_violin_ && traces_.front()->has_x()) {
            figure_.layout().violin_mode("group");
            figure_.layout().xaxis().type("category");
        }
        if (is_box_ && traces_.front()->has_x()) {
            figure_.layout().box_mode("group");
            figure_.layout().xaxis().type("category");
        }

        util::prepare_directory_for(file_path);
        plotly_plotter::write_html(file_path, figure_);
    }

private:
    //! Traces.
    std::vector<std::shared_ptr<IPlotlyTrace>> traces_;

    //! Figure.
    plotly_plotter::figure figure_;

    //! Whether this plot is a violin plot.
    bool is_violin_{false};

    //! Whether this plot is a box plot.
    bool is_box_{false};

    //! Whether y-axis is in log scale.
    bool is_log_y_{false};
};

/*!
 * \brief Class to plot data using plotly.
 */
class PlotlyPlotter final : public IPlotter {
public:
    /*!
     * \brief Constructor.
     */
    PlotlyPlotter() = default;

    PlotlyPlotter(const PlotlyPlotter&) = delete;
    PlotlyPlotter(PlotlyPlotter&&) = delete;
    auto operator=(const PlotlyPlotter&) -> PlotlyPlotter& = delete;
    auto operator=(PlotlyPlotter&&) -> PlotlyPlotter& = delete;

    /*!
     * \brief Destructor.
     */
    ~PlotlyPlotter() override = default;

    //! \copydoc stat_bench::plots::IPlotter::create_figure
    [[nodiscard]] auto create_figure(const util::Utf8String& title)
        -> std::unique_ptr<IFigure> override {
        return std::make_unique<PlotlyFigure>(title);
    }
};

auto create_plotly_plotter() -> std::shared_ptr<IPlotter> {
    return std::make_shared<PlotlyPlotter>();
}

}  // namespace plots
}  // namespace stat_bench
