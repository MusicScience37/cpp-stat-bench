/*
 * Copyright 2021 MusicScience37 (Kenta Kabashima)
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
 * \brief Test of ViolinPlotReporter class.
 */
#include "stat_bench/reporter/violin_plot_reporter.h"

#include <memory>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "read_file.h"
#include "remove_directory.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/system_clock.h"
#include "use_reporter_for_test.h"

TEST_CASE("stat_bench::reporter::ViolinPlotReporter") {
    using stat_bench::clock::Duration;
    using stat_bench::clock::SystemClock;
    using stat_bench::measurer::Measurement;

    SECTION("write") {
        const auto prefix = std::string("./ViolinPlotReporter");
        remove_directory(prefix);

        const auto reporter =
            std::make_shared<stat_bench::reporter::ViolinPlotReporter>(prefix);
        REQUIRE_NOTHROW(stat_bench_test::use_reporter_for_test(reporter.get()));

        ApprovalTests::Approvals::verify(
            stat_bench_test::read_file(
                fmt::format("{}/Group1/Measurement1_violin.html", prefix)),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
