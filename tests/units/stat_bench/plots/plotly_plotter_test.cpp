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
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "../reporter/read_file.h"
#include "stat_bench/util/utf8_string.h"

TEST_CASE("stat_bench::plots::PlotlyPlotter") {
    using stat_bench::util::Utf8String;

    auto plotter = stat_bench::plots::create_plotly_plotter();

    SECTION("create a simple line plot") {
        auto figure = plotter->create_figure(Utf8String("Simple Line Plot"));

        // NOLINTNEXTLINE(*-magic-numbers)
        figure->add_line({1.0, 2.0, 3.0}, {1.1, 2.2, 3.3}, Utf8String("Line1"));
        // NOLINTNEXTLINE(*-magic-numbers)
        figure->add_line({2.0, 3.0, 4.0}, {3.3, 4.4, 5.5}, Utf8String("Line2"));

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

        // NOLINTNEXTLINE(*-magic-numbers)
        figure->add_line({1.0, 2.0, 3.0}, {1.1, 2.2, 3.3}, Utf8String("Line1"));
        // NOLINTNEXTLINE(*-magic-numbers)
        figure->add_line({2.0, 3.0, 4.0}, {3.3, 4.4, 5.5}, Utf8String("Line2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_x();
        figure->set_log_y();

        const auto file_path = std::string("./PlotlyPlotter/LogLinePlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a line plot with sequential number") {
        auto figure = plotter->create_figure(
            Utf8String("Line Plot with Sequential Number"));

        figure->add_line_with_sequential_number(
            // NOLINTNEXTLINE(*-magic-numbers)
            {1.1, 2.2, 3.3}, Utf8String("Line1"));

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

        // NOLINTNEXTLINE(*-magic-numbers)
        figure->add_violin({1.1, 2.2, 2.2, 3.3, 11.0}, Utf8String("Violin1"));
        // NOLINTNEXTLINE(*-magic-numbers)
        figure->add_violin({3.3, 4.4, 4.4, 5.5}, Utf8String("Violin2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));

        const auto file_path = std::string("./PlotlyPlotter/ViolinPlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create a violin plot in log scale") {
        auto figure = plotter->create_figure(Utf8String("Log Violin Plot"));

        // NOLINTNEXTLINE(*-magic-numbers)
        figure->add_violin({1.0, 2.2, 2.2, 3.3, 11.0}, Utf8String("Violin1"));
        figure->add_violin(
            // NOLINTNEXTLINE(*-magic-numbers)
            {3.3e+2, 4.4e+2, 4.4e+2, 5.5e+2, 1e+3}, Utf8String("Violin2"));

        figure->set_x_title(Utf8String("X"));
        figure->set_y_title(Utf8String("Y"));
        figure->set_log_y();

        const auto file_path =
            std::string("./PlotlyPlotter/LogViolinPlot.html");
        figure->write_to_file(file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
