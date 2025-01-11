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
#include <cstddef>
#include <fstream>
#include <limits>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include <nlohmann/json.hpp>

#include "i_plotly_trace.h"
#include "line_trace.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/plots/jinja_renderer.h"
#include "stat_bench/util/prepare_directory.h"
#include "stat_bench/util/utf8_string.h"
#include "template/plotly_plot.h"

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
     * \param[in] renderer Renderer.
     */
    PlotlyFigure(const util::Utf8String& title, JinjaRenderer& renderer)
        : data_(nlohmann::json::array()),
          layout_(nlohmann::json::object()),
          config_(nlohmann::json::object()),
          title_(title.str()),
          renderer_(renderer) {
        layout_["title"] = title.str();

        layout_["xaxis"]["type"] = "-";
        layout_["yaxis"]["type"] = "-";
        layout_["layout"]["showlegend"] = true;

        config_["scrollZoom"] = true;
        config_["responsive"] = true;
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
        auto trace = std::make_shared<LineTrace>();
        traces_.push_back(trace);
        return trace;
    }

    //! \copydoc stat_bench::plots::IFigure::add_violin
    void add_violin(
        const std::vector<double>& y, const util::Utf8String& name) override {
        nlohmann::json trace;
        trace["y"] = y;
        trace["type"] = "violin";
        trace["name"] = name.str();
        trace["box"]["visible"] = true;
        trace["meanline"]["visible"] = true;
        trace["points"] = "outliers";
        data_.push_back(trace);

        for (const auto& value : y) {
            max_y_ = std::max(max_y_, value);
            min_y_ = std::min(min_y_, value);
        }

        is_violin_ = true;
    }

    //! \copydoc stat_bench::plots::IFigure::add_text_to_last_trace
    void add_text_to_last_trace(
        const std::vector<util::Utf8String>& texts) override {
        auto& trace = data_.back();
        auto& text_json = trace["text"];
        text_json = nlohmann::json::array();
        for (const auto& text : texts) {
            text_json.push_back(text.str());
        }
    }

    //! \copydoc stat_bench::plots::IFigure::set_x_title
    void set_x_title(const util::Utf8String& title) override {
        layout_["xaxis"]["title"] = title.str();
    }

    //! \copydoc stat_bench::plots::IFigure::set_y_title
    void set_y_title(const util::Utf8String& title) override {
        layout_["yaxis"]["title"] = title.str();
    }

    //! \copydoc stat_bench::plots::IFigure::set_log_x
    void set_log_x() override { layout_["xaxis"]["type"] = "log"; }

    //! \copydoc stat_bench::plots::IFigure::set_log_y
    void set_log_y() override {
        layout_["yaxis"]["type"] = "log";
        is_log_y_ = true;
    }

    //! \copydoc stat_bench::plots::IFigure::write_to_file
    void write_to_file(const std::string& file_path) override {
        for (const auto& trace : traces_) {
            data_.push_back(trace->data());
            const auto [trace_min_y, trace_max_y] = trace->y_range();
            min_y_ = std::min(min_y_, trace_min_y);
            max_y_ = std::max(max_y_, trace_max_y);
        }

        if (is_violin_ && is_log_y_) {
            // For this case, spacial treatment is needed to prevent wrong
            // automatic range in plotly library.
            constexpr double margin_in_log = 0.17;
            const double lower_bound_in_log =
                std::log10(min_y_) - margin_in_log;
            const double upper_bound_in_log =
                std::log10(max_y_) + margin_in_log;
            layout_["yaxis"]["range"] =
                std::vector<double>{lower_bound_in_log, upper_bound_in_log};
            layout_["yaxis"]["constrain"] = "range";
        }

        nlohmann::json input;
        input["title"] = title_;
        input["dataset"]["data"] = data_;
        input["dataset"]["layout"] = layout_;
        input["dataset"]["config"] = config_;

        util::prepare_directory_for(file_path);
        std::ofstream stream{file_path};
        renderer_.render_to(stream, "plotly_plot", input);
    }

private:
    //! Traces.
    std::vector<std::shared_ptr<IPlotlyTrace>> traces_;

    //! Data in plotly.
    nlohmann::json data_;

    //! Layout in plotly.
    nlohmann::json layout_;

    //! Config in plotly.
    nlohmann::json config_;

    //! Title of the figure.
    std::string title_;

    //! Renderer.
    JinjaRenderer& renderer_;

    //! Maximum value of x-axis.
    double max_x_{-std::numeric_limits<double>::infinity()};

    //! Minimum value of x-axis.
    double min_x_{std::numeric_limits<double>::infinity()};

    //! Maximum value of y-axis.
    double max_y_{-std::numeric_limits<double>::infinity()};

    //! Minimum value of y-axis.
    double min_y_{std::numeric_limits<double>::infinity()};

    //! Whether this plot is a violin plot.
    bool is_violin_{false};

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
    PlotlyPlotter() { renderer_.load_from_text("plotly_plot", plotly_plot); }

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
        return std::make_unique<PlotlyFigure>(title, renderer_);
    }

private:
    //! Renderer.
    JinjaRenderer renderer_;
};

auto create_plotly_plotter() -> std::shared_ptr<IPlotter> {
    return std::make_shared<PlotlyPlotter>();
}

}  // namespace plots
}  // namespace stat_bench
