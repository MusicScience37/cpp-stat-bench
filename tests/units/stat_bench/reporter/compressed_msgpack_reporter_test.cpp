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
 * \brief Test of CompressedMsgPackReporter class.
 */
#include "stat_bench/reporter/compressed_msgpack_reporter.h"

#include <array>
#include <cstddef>
#include <memory>
#include <regex>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>
#include <msgpack_light/memory_output_stream.h>
#include <nlohmann/json.hpp>
#include <zlib.h>

#include "stat_bench/clock/duration.h"
#include "stat_bench/clock/system_clock.h"
#include "stat_bench/measurer/measurement.h"
#include "use_reporter_for_test.h"

TEST_CASE("stat_bench::reporter::CompressedMsgPackReporter") {
    using stat_bench::clock::Duration;
    using stat_bench::clock::SystemClock;
    using stat_bench::measurer::Measurement;

    SECTION("write") {
        const auto filepath =
            std::string("./CompressedMsgPackReporterTest.data.gz");

        const auto reporter =
            std::make_shared<stat_bench::reporter::CompressedMsgPackReporter>(
                filepath);
        REQUIRE_NOTHROW(stat_bench_test::use_reporter_for_test(reporter.get()));

        msgpack_light::memory_output_stream uncompressed_data;
        {
            constexpr std::size_t buf_size = 1024;
            std::array<char, buf_size> buf{};
            gzFile file = gzopen(filepath.c_str(), "rb");
            while (true) {
                const int res = gzread(file, buf.data(), buf.size());
                REQUIRE(res >= 0);
                if (res == 0) {
                    break;
                }
                uncompressed_data.write(
                    reinterpret_cast<const unsigned char*>(buf.data()),
                    static_cast<std::size_t>(res));
                if (static_cast<std::size_t>(res) < buf.size()) {
                    break;
                }
            }
            (void)gzclose(file);
        }

        const auto data_json =
            nlohmann::json::from_msgpack(uncompressed_data.data(),
                uncompressed_data.data() + uncompressed_data.size());

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
