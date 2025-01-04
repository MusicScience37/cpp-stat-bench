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
 * \brief Test of OrderedMap class.
 */
#include "stat_bench/util/ordered_map.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::util::OrderedMap") {
    using stat_bench::util::OrderedMap;

    SECTION("add and get values using operator[]") {
        OrderedMap<int, std::string> map;

        map[2] = "two";
        map[1] = "one";

        CHECK(map[2] == "two");
        CHECK(map[1] == "one");
        CHECK(map[3] == "");
    }

    SECTION("get values using at function") {
        OrderedMap<int, std::string> map;

        map[2] = "two";
        map[1] = "one";

        CHECK(map.at(2) == "two");
        CHECK(map.at(1) == "one");
        CHECK_THROWS((void)map.at(3));
    }

    SECTION("iterate over pairs") {
        OrderedMap<int, std::string> map;

        map[2] = "two";
        map[1] = "one";

        std::vector<std::pair<int, std::string>> pairs;
        for (const auto& pair : map) {
            pairs.push_back(pair);
        }

        CHECK(pairs ==
            std::vector<std::pair<int, std::string>>{{2, "two"}, {1, "one"}});
    }
}
