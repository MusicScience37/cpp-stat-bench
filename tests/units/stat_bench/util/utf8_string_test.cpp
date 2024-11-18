/*
 * Copyright 2024 MusicScience37 (Kenta Kabashima)
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
 * \brief Test of Utf8String class.
 */
#include "stat_bench/util/utf8_string.h"

#include <sstream>
#include <unordered_set>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/custom_output_name.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/parameter_name.h"

TEST_CASE("create Utf8String") {
    using TestType = stat_bench::util::Utf8String;

    SECTION("create from a string") {
        const std::string data = "abc";

        const TestType str(data);

        CHECK(str.str() == data);
    }

    SECTION("create an empty string") {
        const TestType str;

        CHECK(str.str() == "");  // NOLINT
    }
}

TEMPLATE_TEST_CASE("create UTF8 strings", "",
    stat_bench::measurer::MeasurerName, stat_bench::param::ParameterName,
    stat_bench::BenchmarkCaseName, stat_bench::BenchmarkGroupName,
    stat_bench::CustomOutputName) {
    SECTION("create from a string") {
        const std::string data = "abc";

        const TestType str(data);

        CHECK(str.str().str() == data);
    }

    SECTION("create from a Utf8String") {
        const stat_bench::util::Utf8String data("abc");

        const TestType str(data);

        CHECK(str.str().str() == data.str());
    }
}

TEST_CASE("compare Utf8String for equality") {
    using TestType = stat_bench::util::Utf8String;

    SECTION("compare") {
        const TestType str1("abc");
        const TestType str2("abc");
        const TestType str3("def");

        CHECK(str1 == str2);
        CHECK_FALSE(str1 == str3);
        CHECK_FALSE(str1 != str2);
        CHECK(str1 != str3);
    }
}

TEMPLATE_TEST_CASE("compare UTF8 strings for equality", "",
    stat_bench::measurer::MeasurerName, stat_bench::param::ParameterName,
    stat_bench::BenchmarkCaseName, stat_bench::BenchmarkGroupName,
    stat_bench::CustomOutputName) {
    SECTION("compare") {
        const TestType str1("abc");
        const TestType str2("abc");
        const TestType str3("def");

        CHECK(str1 == str2);
        CHECK_FALSE(str1 == str3);

        CHECK_FALSE(str1 != str2);
        CHECK(str1 != str3);
    }
}

TEST_CASE("compare Utf8String for ordering") {
    using TestType = stat_bench::util::Utf8String;

    SECTION("compare") {
        const TestType str1("abc");
        const TestType str2("abc");
        const TestType str3("def");

        CHECK(str1 < str3);
        CHECK_FALSE(str1 < str2);
        CHECK_FALSE(str3 < str1);

        CHECK_FALSE(str1 > str3);
        CHECK_FALSE(str1 > str2);
        CHECK(str3 > str1);

        CHECK(str1 <= str3);
        CHECK(str1 <= str2);
        CHECK_FALSE(str3 <= str1);

        CHECK_FALSE(str1 >= str3);
        CHECK(str1 >= str2);
        CHECK(str3 >= str1);
    }
}

TEMPLATE_TEST_CASE(
    "compare UTF8 strings for ordering", "", stat_bench::param::ParameterName) {
    SECTION("compare") {
        const TestType str1("abc");
        const TestType str2("abc");
        const TestType str3("def");

        CHECK(str1 < str3);
        CHECK_FALSE(str1 < str2);
        CHECK_FALSE(str3 < str1);

        CHECK_FALSE(str1 > str3);
        CHECK_FALSE(str1 > str2);
        CHECK(str3 > str1);

        CHECK(str1 <= str3);
        CHECK(str1 <= str2);
        CHECK_FALSE(str3 <= str1);

        CHECK_FALSE(str1 >= str3);
        CHECK(str1 >= str2);
        CHECK(str3 >= str1);
    }
}

TEST_CASE("format Utf8String") {
    using TestType = stat_bench::util::Utf8String;

    SECTION("via fmt library") {
        const TestType str("abc");

        const std::string formatted = fmt::format("{}", str);

        CHECK(formatted == "abc");
    }

    SECTION("via std::ostream") {
        const TestType str("abc");

        std::ostringstream stream;
        stream << str;

        CHECK(stream.str() == "abc");
    }
}

TEMPLATE_TEST_CASE("format UTF8 strings", "",
    stat_bench::measurer::MeasurerName, stat_bench::param::ParameterName,
    stat_bench::BenchmarkCaseName, stat_bench::BenchmarkGroupName,
    stat_bench::CustomOutputName) {
    SECTION("via fmt library") {
        const TestType str("abc");

        const std::string formatted = fmt::format("{}", str);

        CHECK(formatted == "abc");
    }

    SECTION("via std::ostream") {
        const TestType str("abc");

        std::ostringstream stream;
        stream << str;

        CHECK(stream.str() == "abc");
    }
}

TEST_CASE("hash Utf8String") {
    using TestType = stat_bench::util::Utf8String;

    SECTION("calculate hash") {
        const TestType str1("abc");
        const TestType str2("abc");
        const TestType str3("abd");

        const std::hash<TestType> hasher{};

        CHECK(hasher(str1) == hasher(str2));
        CHECK(hasher(str1) != hasher(str3));
    }

    SECTION("use in std::unordered_set") {
        const TestType str1("abc");
        const TestType str2("def");
        const TestType str3("ghi");

        std::unordered_set<TestType> set;
        set.insert(str1);
        set.insert(str2);

        CHECK(set.size() == 2);
        CHECK(set.count(str1) == 1);
        CHECK(set.count(str2) == 1);
        CHECK(set.count(str3) == 0);
    }
}

TEMPLATE_TEST_CASE("hash UTF8 strings", "", stat_bench::param::ParameterName) {
    SECTION("calculate hash") {
        const TestType str1("abc");
        const TestType str2("abc");
        const TestType str3("abd");

        const std::hash<TestType> hasher{};

        CHECK(hasher(str1) == hasher(str2));
        CHECK(hasher(str1) != hasher(str3));
    }

    SECTION("use in std::unordered_set") {
        const TestType str1("abc");
        const TestType str2("def");
        const TestType str3("ghi");

        std::unordered_set<TestType> set;
        set.insert(str1);
        set.insert(str2);

        CHECK(set.size() == 2);
        CHECK(set.count(str1) == 1);
        CHECK(set.count(str2) == 1);
        CHECK(set.count(str3) == 0);
    }
}
