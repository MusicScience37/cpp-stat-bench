/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
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
 * \brief Test of MsgPackReporter class.
 */
#include "stat_bench/reporter/msgpack_reporter.h"

#include <fstream>
#include <functional>
#include <initializer_list>
#include <memory>
#include <regex>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/system_clock.h"
#include "use_reporter_for_test.h"

TEST_CASE("stat_bench::reporter::MsgPackReporter") {
    using stat_bench::clock::Duration;
    using stat_bench::clock::SystemClock;
    using stat_bench::measurer::Measurement;

    SECTION("write") {
        const auto filepath = std::string("./MsgPackReporterTest.data");

        const auto reporter =
            std::make_shared<stat_bench::reporter::MsgPackReporter>(filepath);
        REQUIRE_NOTHROW(stat_bench_test::use_reporter_for_test(reporter.get()));

        std::ifstream stream{filepath};
        REQUIRE(stream);
        const auto data_json = nlohmann::json::from_msgpack(stream);

        ApprovalTests::Approvals::verify(data_json.dump(2),
            ApprovalTests::Options()
                .withScrubber(
                    [time_scrubber = ApprovalTests::Scrubbers::createRegexScrubber(
                         R"(\d\d\d\d-\d\d-\d\dT\d\d:\d\d:\d\d\.\d\d\d\d\d\d[+-]\d\d\d\d)",
                         "<time>"),
                        float3_scrubber =
                            ApprovalTests::Scrubbers::createRegexScrubber(
                                std::regex(
                                    R"([-]?(0|[1-9][0-9]*)(\.[0-9]+)?([eE][+-]?[0-9]+)?)"),
                                [](const std::ssub_match& match)
                                    -> std::string {
                                    auto str = match.str();
                                    const auto val = nlohmann::json::parse(str);
                                    if (val.is_number_integer()) {
                                        return str;
                                    }
                                    return fmt::format(
                                        "{:.3e}", val.get<double>());
                                })](const std::string& contents) {
                        return float3_scrubber(time_scrubber(contents));
                    })
                .fileOptions()
                .withFileExtension(".json"));
    }
}
