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
 * \brief Test of ParameterGenerator class.
 */
#include "stat_bench/param/parameter_generator.h"

#include <memory>

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/param/parameter_value_vector.h"

TEST_CASE("stat_bench::param::ParameterGenerator") {
    SECTION("generate") {
        std::vector<std::pair<std::string,
            std::shared_ptr<stat_bench::param::IParameterValueVector>>>
            params;

        const auto param1 =
            std::make_shared<stat_bench::param::ParameterValueVector<int>>();
        constexpr int val11 = 3;
        constexpr int val12 = 5;
        param1->add(val11)->add(val12);
        params.emplace_back("param1", param1);

        const auto param2 = std::make_shared<
            stat_bench::param::ParameterValueVector<std::string>>();
        const auto val21 = std::string("1");
        const auto val22 = std::string("2");
        const auto val23 = std::string("3");
        param2->add(val21)->add(val22)->add(val23);
        params.emplace_back("param2", param2);

        stat_bench::param::ParameterGenerator generator{params};

        auto dict = generator.generate();
        REQUIRE(dict.get<int>("param1") == val11);
        REQUIRE(dict.get<std::string>("param2") == val21);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>("param1") == val11);
        REQUIRE(dict.get<std::string>("param2") == val22);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>("param1") == val11);
        REQUIRE(dict.get<std::string>("param2") == val23);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>("param1") == val12);
        REQUIRE(dict.get<std::string>("param2") == val21);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>("param1") == val12);
        REQUIRE(dict.get<std::string>("param2") == val22);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>("param1") == val12);
        REQUIRE(dict.get<std::string>("param2") == val23);

        REQUIRE(!generator.iterate());
    }

    SECTION("generate when no parameter is set") {
        std::vector<std::pair<std::string,
            std::shared_ptr<stat_bench::param::IParameterValueVector>>>
            params;

        stat_bench::param::ParameterGenerator generator{params};

        auto dict = generator.generate();
        // NOLINTNEXTLINE
        CHECK(dict.as_string_dict() ==
            std::unordered_map<std::string, std::string>());

        REQUIRE(!generator.iterate());
    }
}
