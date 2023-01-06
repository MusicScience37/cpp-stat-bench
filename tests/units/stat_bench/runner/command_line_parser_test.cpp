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
 * \brief Test of CommandLineParser class.
 */
#include "stat_bench/runner/command_line_parser.h"

#include <exception>
#include <stdexcept>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>

#include "../measurer/mock_measurer.h"
#include "../mock_benchmark_case.h"
#include "../reporter/mock_reporter.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/param/parameter_config.h"
#include "stat_bench/param/parameter_value_vector.h"

TEST_CASE("stat_bench::runner::CommandLineParser") {
    stat_bench::runner::CommandLineParser parser;

    SECTION("parse --help") {
        const int argc = 2;
        char arg0[] = "test_bench";                  // NOLINT
        char arg1[] = "--help";                      // NOLINT
        const char* argv[] = {arg0, arg1, nullptr};  // NOLINT

        REQUIRE_NOTHROW(parser.parse_cli(argc, argv));
        REQUIRE(parser.config().show_help);
    }
}
