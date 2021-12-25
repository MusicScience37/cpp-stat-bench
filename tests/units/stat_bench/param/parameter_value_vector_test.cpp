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
 * \brief Test of ParameterValueVector class.
 */
#include "stat_bench/param/parameter_value_vector.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("stat_bench::param::ParameterValueVector") {
    SECTION("add values") {
        const auto vec = std::make_shared<
            stat_bench::param::ParameterValueVector<std::string>>();

        vec->add("Test1")->add("Test2");
        REQUIRE(vec->size() == 2);

        auto iter = vec->begin();
        auto end = vec->end();
        REQUIRE(iter != end);
        REQUIRE(iter->as<std::string>() == "Test1");

        ++iter;
        REQUIRE(iter != end);
        REQUIRE(iter->as<std::string>() == "Test2");

        ++iter;
        REQUIRE(iter == end);
    }
}
