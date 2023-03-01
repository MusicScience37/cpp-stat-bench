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
 * \brief Test of check_glob_pattern function.
 */
#include "stat_bench/util/check_glob_pattern.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::util::check_glob_pattern") {
    using stat_bench::util::check_glob_pattern;

    SECTION("no pattern") {
        CHECK(check_glob_pattern("test", "test"));
        CHECK(check_glob_pattern("any", "any"));
        CHECK(check_glob_pattern("", ""));
        CHECK_FALSE(check_glob_pattern("test", "tes"));
        CHECK_FALSE(check_glob_pattern("test", "test1"));
        CHECK_FALSE(check_glob_pattern("test", "1test"));
    }

    SECTION("one asterisk only") {
        CHECK(check_glob_pattern("*", ""));
        CHECK(check_glob_pattern("*", "t"));
        CHECK(check_glob_pattern("*", "test"));
    }

    SECTION("one asterisk at the beginning") {
        CHECK(check_glob_pattern("*test", "test"));
        CHECK(check_glob_pattern("*test", "1test"));
        CHECK(check_glob_pattern("*test", "123test"));
        CHECK_FALSE(check_glob_pattern("*test", "1est"));
        CHECK_FALSE(check_glob_pattern("*test", "1test1"));
    }

    SECTION("one asterisk at the end") {
        CHECK(check_glob_pattern("test*", "test"));
        CHECK(check_glob_pattern("test*", "test1"));
        CHECK(check_glob_pattern("test*", "test123"));
        CHECK_FALSE(check_glob_pattern("test*", "tes"));
    }

    SECTION("one asterisk in the pattern") {
        CHECK(
            check_glob_pattern("test*any", "testany"));  // cspell: disable-line
        CHECK(check_glob_pattern("test*any", "test_any"));
        CHECK(check_glob_pattern("test*any", "test123any"));
    }

    SECTION("multiple asterisks") {
        CHECK(check_glob_pattern("test*any*", "test_any"));
        CHECK(check_glob_pattern("test*any*", "test_any123"));
    }

    SECTION("multiple sequential asterisks") {
        CHECK(check_glob_pattern(
            "test**any", "testany"));  // cspell: disable-line
        CHECK(check_glob_pattern("test**any", "test_any"));
        CHECK(check_glob_pattern("test**any", "test123any"));
    }
}
