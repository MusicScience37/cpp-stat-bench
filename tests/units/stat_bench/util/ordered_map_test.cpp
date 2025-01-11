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

#include <string>
#include <tuple>

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

    SECTION("check size") {
        OrderedMap<int, std::string> map;

        CHECK(map.size() == 0);  // NOLINT
        CHECK(map.empty());

        map[2] = "two";

        CHECK(map.size() == 1);
        CHECK_FALSE(map.empty());

        map[1] = "one";

        CHECK(map.size() == 2);
        CHECK_FALSE(map.empty());
    }

    SECTION("add pairs using emplace function") {
        OrderedMap<int, std::string> map;

        auto [iter, success] = map.emplace(2, "two");
        CHECK(iter->first == 2);
        CHECK(iter->second == "two");
        CHECK(success);
        CHECK(map[2] == "two");

        std::tie(iter, success) = map.emplace(2, "one");
        CHECK(iter->first == 2);
        CHECK(iter->second == "two");
        CHECK_FALSE(success);
        CHECK(map[2] == "two");
    }

    SECTION("erase pairs using erase function") {
        OrderedMap<int, std::string> map;

        map[2] = "two";
        map[1] = "one";

        map.erase(map.begin());
        CHECK(map.size() == 1);
        CHECK(map[1] == "one");
        CHECK_THROWS(map.at(2));
    }

    SECTION("get values using at function") {
        OrderedMap<int, std::string> map;

        map[2] = "two";
        map[1] = "one";

        CHECK(map.at(2) == "two");
        CHECK(map.at(1) == "one");
        CHECK_THROWS((void)map.at(3));
    }

    SECTION("find values using find function") {
        OrderedMap<int, std::string> map;

        map[2] = "two";
        map[1] = "one";

        CHECK(map.find(2)->second == "two");
        CHECK(map.find(1)->second == "one");
        CHECK(map.find(3) == map.end());
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

    SECTION("compare maps") {
        const OrderedMap<int, std::string> map1{{2, "two"}, {1, "one"}};
        const OrderedMap<int, std::string> map2{{1, "one"}, {2, "two"}};
        const OrderedMap<int, std::string> map3{
            {1, "one"}, {2, "two"}, {3, "three"}};

        CHECK(map1 == map2);
        CHECK_FALSE(map1 == map3);
        CHECK_FALSE(map2 == map3);
        CHECK_FALSE(map1 != map2);
        CHECK(map1 != map3);
        CHECK(map2 != map3);
    }
}
