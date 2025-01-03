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
 * \brief Test of ParameterValue class.
 */
#include "stat_bench/param/parameter_value.h"

#include <functional>

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/util/utf8_string.h"

TEST_CASE("stat_bench::param::ParameterValue") {
    SECTION("check type") {
        stat_bench::param::ParameterValue value;
        REQUIRE(!value.is_type_of<int>());
        REQUIRE(!value.is_type_of<std::string>());

        const int val1 = 5;
        value.emplace<int>(val1);
        REQUIRE(value.is_type_of<int>());
        REQUIRE(!value.is_type_of<std::string>());

        const char* val2 = "Test";
        value.emplace<std::string>(val2);
        REQUIRE(!value.is_type_of<int>());
        REQUIRE(value.is_type_of<std::string>());

        value.clear();
        REQUIRE(!value.is_type_of<int>());
        REQUIRE(!value.is_type_of<std::string>());
    }

    SECTION("get value") {
        stat_bench::param::ParameterValue value;
        REQUIRE_THROWS((void)value.as<int>());
        REQUIRE_THROWS((void)value.as<std::string>());

        const int val1 = 5;
        value.emplace<int>(val1);
        REQUIRE(value.as<int>() == val1);
        REQUIRE_THROWS((void)value.as<std::string>());

        const char* val2 = "Test";
        value.emplace<std::string>(val2);
        REQUIRE_THROWS((void)value.as<int>());
        REQUIRE(value.as<std::string>() == val2);

        value.clear();
        REQUIRE_THROWS((void)value.as<int>());
        REQUIRE_THROWS((void)value.as<std::string>());
    }

    SECTION("format to string") {
        stat_bench::param::ParameterValue value;
        REQUIRE(value.to_string().str() == "null");

        const int val1 = 5;
        value.emplace<int>(val1);
        REQUIRE(value.to_string().str() == "5");

        const char* val2 = "Test";
        value.emplace<std::string>(val2);
        REQUIRE(value.to_string().str() == "Test");

        value.clear();
        REQUIRE(value.to_string().str() == "null");
    }

    SECTION("convert to double") {
        stat_bench::param::ParameterValue value;
        REQUIRE_THROWS((void)value.to_double());

        const int val1 = 5;
        value.emplace<int>(val1);
        REQUIRE(value.to_double() == 5.0);  // NOLINT(*-magic-numbers)

        const char* val2 = "Test";
        value.emplace<std::string>(val2);
        REQUIRE_THROWS((void)value.to_double());

        value.clear();
        REQUIRE_THROWS((void)value.to_double());
    }

    SECTION("calculate hash value") {
        // Since the hash can differ between platforms,
        // here we only check if the function finishes correctly.
        stat_bench::param::ParameterValue value;
        std::hash<stat_bench::param::ParameterValue> hash;
        REQUIRE_NOTHROW(hash(value));

        const int val1 = 5;
        value.emplace<int>(val1);
        REQUIRE_NOTHROW(hash(value));

        const char* val2 = "Test";
        value.emplace<std::string>(val2);
        REQUIRE_NOTHROW(hash(value));

        value.clear();
        REQUIRE_NOTHROW(hash(value));
    }

    SECTION("check equality") {
        stat_bench::param::ParameterValue value1;
        stat_bench::param::ParameterValue value2;
        REQUIRE(value1 == value2);

        const int val1 = 5;
        value1.emplace<int>(val1);
        REQUIRE(value1 != value2);

        value2.emplace<int>(val1);
        REQUIRE(value1 == value2);

        const char* val2 = "Test";
        value1.emplace<std::string>(val2);
        REQUIRE(value1 != value2);

        value2.emplace<std::string>(val2);
        REQUIRE(value1 == value2);

        value1.clear();
        REQUIRE(value1 != value2);

        value2.clear();
        REQUIRE(value1 == value2);
    }

    SECTION("copy") {
        stat_bench::param::ParameterValue value1;
        stat_bench::param::ParameterValue value2;
        const char* val = "Test";
        value2 = value1.emplace<std::string>(val);

        REQUIRE(value1.as<std::string>() == val);
        REQUIRE(value2.as<std::string>() == val);
    }

    SECTION("move") {
        stat_bench::param::ParameterValue value1;
        stat_bench::param::ParameterValue value2;
        const char* val = "Test";
        value2 = std::move(value1.emplace<std::string>(val));

        REQUIRE_THROWS((void)value1.as<std::string>());  // NOLINT
        REQUIRE(value2.as<std::string>() == val);
    }
}
