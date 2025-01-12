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
 * \brief Test of PlotlyPlotter class.
 */
#include "stat_bench/plots/plotly_plotter.h"

// clang-format off
// ApprovalTests requires fmt library to be included.
#include <fmt/format.h> // IWYU pragma: keep
#include <ApprovalTests.hpp>
// clang-format on

#include <string>
#include <variant>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "../reporter/read_file.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/util/utf8_string.h"

TEST_CASE("stat_bench::plots::PlotlyPlotter") {
    using stat_bench::param::ParameterValueVariant;
    using stat_bench::util::Utf8String;
    using std::string_literals::operator""s;

    auto plotter = stat_bench::plots::create_plotly_plotter();

    SECTION("create a simple line plot") {
        auto figure = plotter->create_figure(Utf8String("Simple Line Plot"));

        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{1.0, 2.0, 3.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            ->name(Utf8String("Line1"));
        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{2.0, 3.0, 4.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));

        const auto file_path =
            std::string("./PlotlyPlotter/SimpleLinePlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot in log scale") {
        auto figure = plotter->create_figure(Utf8String("Log Line Plot"));

        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{1.0, 2.0, 3.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            ->name(Utf8String("Line1"));
        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{2.0, 3.0, 4.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_x();
        figure->set_log_y();

        const auto file_path = std::string("./PlotlyPlotter/LogLinePlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot using string parameters") {
        auto figure = plotter->create_figure(Utf8String("Parameter Line Plot"));

        figure->add_line_trace()
            ->x(std::vector<ParameterValueVariant>{"a"s, "b"s, "c"s})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            ->name(Utf8String("Line1"));
        figure->add_line_trace()
            ->x(std::vector<ParameterValueVariant>{"a"s, "b"s, "c"s})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));

        const auto file_path =
            std::string("./PlotlyPlotter/StringParamLinePlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot with error") {
        auto figure =
            plotter->create_figure(Utf8String("Line Plot with Error"));

        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{1.0, 2.0, 3.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y_error({0.1, 0.2, 0.3})
            ->name(Utf8String("Line1"));
        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{2.0, 3.0, 4.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y_error({0.3, 0.4, 0.5})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_y();

        const auto file_path =
            std::string("./PlotlyPlotter/LinePlotWithError.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot with error and string parameters") {
        auto figure = plotter->create_figure(
            Utf8String("Line Plot with Error and String Parameters"));

        figure->add_line_trace()
            ->x(std::vector<ParameterValueVariant>{"a"s, "b"s, "c"s})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y_error({0.1, 0.2, 0.3})
            ->name(Utf8String("Line1"));
        figure->add_line_trace()
            ->x(std::vector<ParameterValueVariant>{"a"s, "b"s, "c"s})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y_error({0.3, 0.4, 0.5})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_y();

        const auto file_path = std::string(
            "./PlotlyPlotter/LinePlotWithErrorAndStringParameters.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot with error in x") {
        auto figure =
            plotter->create_figure(Utf8String("Line Plot with Error"));

        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{1.0, 2.0, 3.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x_error({0.1, 0.2, 0.3})
            ->name(Utf8String("Line1"));
        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{2.0, 3.0, 4.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x_error({0.3, 0.4, 0.5})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_x();

        const auto file_path =
            std::string("./PlotlyPlotter/LinePlotWithXError.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot with error in x and y") {
        auto figure =
            plotter->create_figure(Utf8String("Line Plot with Error"));

        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{1.0, 2.0, 3.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x_error({0.1, 0.2, 0.3})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y_error({0.4, 0.5, 0.6})
            ->name(Utf8String("Line1"));
        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{2.0, 3.0, 4.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x_error({0.3, 0.4, 0.5})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y_error({0.6, 0.7, 0.8})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_x();

        const auto file_path =
            std::string("./PlotlyPlotter/LinePlotWithXYError.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot with sequential number") {
        auto figure = plotter->create_figure(
            Utf8String("Line Plot with Sequential Number"));

        figure->add_line_trace()
            ->generate_sequential_number_for_x(3)
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            ->name(Utf8String("Line1"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));

        const auto file_path =
            std::string("./PlotlyPlotter/LinePlotWithSequentialNumber.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a violin plot") {
        auto figure = plotter->create_figure(Utf8String("Violin Plot"));

        figure
            ->add_violin_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 2.2, 3.3, 11.0})
            ->name(Utf8String("Violin1"));
        figure
            ->add_violin_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 4.4, 5.5})
            ->name(Utf8String("Violin2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));

        const auto file_path = std::string("./PlotlyPlotter/ViolinPlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a violin plot in log scale") {
        auto figure = plotter->create_figure(Utf8String("Log Violin Plot"));

        figure
            ->add_violin_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.0, 2.2, 2.2, 3.3, 11.0})
            ->name(Utf8String("Violin1"));
        figure
            ->add_violin_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3e+2, 4.4e+2, 4.4e+2, 5.5e+2, 1e+3})
            ->name(Utf8String("Violin2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_y();

        const auto file_path =
            std::string("./PlotlyPlotter/LogViolinPlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a violin plot with string parameters") {
        auto figure = plotter->create_figure(
            Utf8String("Violin Plot with String Parameters"));

        figure->add_violin_trace()
            ->x(std::vector<ParameterValueVariant>{
                "a"s, "a"s, "a"s, "a"s, "a"s, "b"s, "b"s, "b"s, "b"s, "b"s})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.0, 2.2, 2.2, 3.3, 11.0, 3.3e2, 4.4e2, 4.4e2, 5.5e2, 1e3})
            ->name(Utf8String("Violin1"));
        figure->add_violin_trace()
            ->x(std::vector<ParameterValueVariant>{
                "a"s, "a"s, "a"s, "a"s, "a"s, "b"s, "b"s, "b"s, "b"s})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.0, 2.2, 2.2, 3.3, 11.0, 3.3, 4.4, 4.4, 5.5})
            ->name(Utf8String("Violin2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_y();

        const auto file_path =
            std::string("./PlotlyPlotter/ViolinPlotWithStringParameters.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot with texts") {
        auto figure =
            plotter->create_figure(Utf8String("Line Plot with Error"));

        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{1.0, 2.0, 3.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({1.1, 2.2, 3.3})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x_error({0.1, 0.2, 0.3})
            ->text(
                {Utf8String{"Text1"}, Utf8String{"Text2"}, Utf8String{"Text3"}})
            ->name(Utf8String("Line1"));
        figure
            ->add_line_trace()
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x(std::vector<double>{2.0, 3.0, 4.0})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->y({3.3, 4.4, 5.5})
            // NOLINTNEXTLINE(*-magic-numbers)
            ->x_error({0.3, 0.4, 0.5})
            ->text(
                {Utf8String{"Text4"}, Utf8String{"Text5"}, Utf8String{"Text6"}})
            ->name(Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_x();

        const auto file_path =
            std::string("./PlotlyPlotter/LinePlotWithText.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
