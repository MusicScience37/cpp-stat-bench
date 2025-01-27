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
 * \brief Test of BoxPlot class.
 */
#include "stat_bench/plots/box_plot.h"

#include <memory>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../reporter/read_file.h"
#include "stat_bench/plots/plotly_plotter.h"
#include "use_plot_for_test.h"

TEST_CASE("stat_bench::plots::BoxPlot") {
    using stat_bench::plots::BoxPlot;
    using stat_bench::plots::create_plotly_plotter;
    using stat_bench_test::use_plot_for_test;

    SECTION("write") {
        const auto plotter = create_plotly_plotter();
        BoxPlot plot;
        const auto file_path = std::string("./plots/BoxPlot.html");
        use_plot_for_test(&plot, plotter.get(), file_path);

        ApprovalTests::Approvals::verify(stat_bench_test::read_file(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
