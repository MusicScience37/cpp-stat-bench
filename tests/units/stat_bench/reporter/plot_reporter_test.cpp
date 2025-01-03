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
 * \brief Test of PlotReporter class.
 */
#include "stat_bench/reporter/plot_reporter.h"

#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "remove_directory.h"
#include "use_reporter_for_test.h"

TEST_CASE("stat_bench::reporter::PlotReporter") {
    SECTION("write") {
        const auto prefix = std::string("./PlotReporter");
        remove_directory(prefix);

        const auto reporter =
            std::make_shared<stat_bench::reporter::PlotReporter>(prefix);
        REQUIRE_NOTHROW(stat_bench_test::use_reporter_for_test(reporter.get()));

        CHECK(std::filesystem::exists(
            fmt::format("{}/Group1/Measurement1_samples.html", prefix)));
        CHECK(std::filesystem::exists(
            fmt::format("{}/Group1/Measurement1_cdf.html", prefix)));
        CHECK(std::filesystem::exists(
            fmt::format("{}/Group1/Measurement1_violin.html", prefix)));
    }
}
