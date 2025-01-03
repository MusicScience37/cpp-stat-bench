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

#include <string>
#include <utility>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"

TEST_CASE("stat_bench::param::ParameterDict") {
    using stat_bench::param::ParameterName;
    using stat_bench::param::ParameterValue;

    SECTION("check parameter existence") {
        std::unordered_map<ParameterName, ParameterValue> data;
        data.emplace(ParameterName("Param1"),
            ParameterValue().emplace<int>(5));  // NOLINT
        data.emplace(ParameterName("Param2"),
            ParameterValue().emplace<std::string>("Value2"));

        const auto dict = stat_bench::param::ParameterDict(std::move(data));

        CHECK(dict.has(ParameterName("Param1")));
        CHECK(dict.has(ParameterName("Param2")));
        CHECK_FALSE(dict.has(ParameterName("Param3")));
    }

    SECTION("get parameter") {
        std::unordered_map<ParameterName, ParameterValue> data;
        data.emplace(ParameterName("Param1"),
            ParameterValue().emplace<int>(5));  // NOLINT
        data.emplace(ParameterName("Param2"),
            ParameterValue().emplace<std::string>("Value2"));

        const auto dict = stat_bench::param::ParameterDict(std::move(data));

        REQUIRE(dict.get<int>(ParameterName("Param1")) == 5);  // NOLINT
        REQUIRE(dict.get<std::string>(ParameterName("Param2")) == "Value2");

        REQUIRE_THROWS((void)dict.get<std::string>(ParameterName("Invalid")));
        REQUIRE_THROWS((void)dict.get<int>(ParameterName("Param2")));

        REQUIRE_THAT(fmt::format("{}", dict),
            Catch::Matchers::ContainsSubstring("Param1=5") &&
                Catch::Matchers::ContainsSubstring("Param2=Value2") &&
                Catch::Matchers::ContainsSubstring(", "));
    }
}
