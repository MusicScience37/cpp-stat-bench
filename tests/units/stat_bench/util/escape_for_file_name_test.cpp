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
 * \brief Test of escape_for_file_name function.
 */
#include "stat_bench/util/escape_for_file_name.h"

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/util/utf8_string.h"

TEST_CASE("stat_bench::util::escape_for_file_name") {
    using stat_bench::util::escape_for_file_name;
    using stat_bench::util::Utf8String;

    SECTION("normal case") {
        const auto input = Utf8String("abc");
        const auto expected = Utf8String("abc");

        const auto result = escape_for_file_name(input);

        CHECK(result == expected);
    }

    SECTION("escape space") {
        const auto input = Utf8String("a b c");
        const auto expected = Utf8String("a%20b%20c");

        const auto result = escape_for_file_name(input);

        CHECK(result == expected);
    }

    SECTION("escape non-ASCII characters") {
        const auto input = Utf8String(u8"あいうえお");
        const auto expected =
            Utf8String("%E3%81%82%E3%81%84%E3%81%86%E3%81%88%E3%81%8A");

        const auto result = escape_for_file_name(input);

        CHECK(result == expected);
    }
}
