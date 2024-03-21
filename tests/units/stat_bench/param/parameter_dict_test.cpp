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
 * \brief Test of ParameterDict class.
 */
#include "stat_bench/param/parameter_dict.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "stat_bench/param/parameter_value.h"

TEST_CASE("stat_bench::param::ParameterDict") {
    SECTION("check parameter existence") {
        std::unordered_map<std::string, stat_bench::param::ParameterValue> data;
        data.emplace("Param1",
            stat_bench::param::ParameterValue().emplace<int>(5));  // NOLINT
        data.emplace("Param2",
            stat_bench::param::ParameterValue().emplace<std::string>("Value2"));

        const auto dict = stat_bench::param::ParameterDict(std::move(data));

        CHECK(dict.has("Param1"));
        CHECK(dict.has("Param2"));
        CHECK_FALSE(dict.has("Param3"));
    }

    SECTION("get parameter") {
        std::unordered_map<std::string, stat_bench::param::ParameterValue> data;
        data.emplace("Param1",
            stat_bench::param::ParameterValue().emplace<int>(5));  // NOLINT
        data.emplace("Param2",
            stat_bench::param::ParameterValue().emplace<std::string>("Value2"));

        const auto dict = stat_bench::param::ParameterDict(std::move(data));

        REQUIRE(dict.get<int>("Param1") == 5);  // NOLINT
        REQUIRE(dict.get<std::string>("Param2") == "Value2");

        REQUIRE_THROWS((void)dict.get<std::string>("Invalid"));
        REQUIRE_THROWS((void)dict.get<int>("Param2"));

        REQUIRE_THAT(fmt::format("{}", dict),
            Catch::Matchers::ContainsSubstring("Param1=5") &&
                Catch::Matchers::ContainsSubstring("Param2=Value2") &&
                Catch::Matchers::ContainsSubstring(", "));
    }
}
