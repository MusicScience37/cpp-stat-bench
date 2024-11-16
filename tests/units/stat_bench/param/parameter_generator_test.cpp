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
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value_vector.h"
#include "stat_bench/util/utf8_string.h"

TEST_CASE("stat_bench::param::ParameterGenerator") {
    using stat_bench::param::IParameterValueVector;
    using stat_bench::param::ParameterName;
    using stat_bench::param::ParameterValueVector;
    using stat_bench::util::Utf8String;

    SECTION("generate") {
        std::vector<
            std::pair<ParameterName, std::shared_ptr<IParameterValueVector>>>
            params;

        const auto param1 = std::make_shared<ParameterValueVector<int>>();
        constexpr int val11 = 3;
        constexpr int val12 = 5;
        param1->add(val11)->add(val12);
        params.emplace_back(ParameterName("param1"), param1);

        const auto param2 =
            std::make_shared<ParameterValueVector<std::string>>();
        const auto val21 = std::string("1");
        const auto val22 = std::string("2");
        const auto val23 = std::string("3");
        param2->add(val21)->add(val22)->add(val23);
        params.emplace_back(ParameterName("param2"), param2);

        stat_bench::param::ParameterGenerator generator{params};

        auto dict = generator.generate();
        REQUIRE(dict.get<int>(ParameterName("param1")) == val11);
        REQUIRE(dict.get<std::string>(ParameterName("param2")) == val21);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>(ParameterName("param1")) == val11);
        REQUIRE(dict.get<std::string>(ParameterName("param2")) == val22);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>(ParameterName("param1")) == val11);
        REQUIRE(dict.get<std::string>(ParameterName("param2")) == val23);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>(ParameterName("param1")) == val12);
        REQUIRE(dict.get<std::string>(ParameterName("param2")) == val21);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>(ParameterName("param1")) == val12);
        REQUIRE(dict.get<std::string>(ParameterName("param2")) == val22);

        REQUIRE(generator.iterate());
        dict = generator.generate();
        REQUIRE(dict.get<int>(ParameterName("param1")) == val12);
        REQUIRE(dict.get<std::string>(ParameterName("param2")) == val23);

        REQUIRE(!generator.iterate());
    }

    SECTION("generate when no parameter is set") {
        std::vector<
            std::pair<ParameterName, std::shared_ptr<IParameterValueVector>>>
            params;

        stat_bench::param::ParameterGenerator generator{params};

        auto dict = generator.generate();
        // NOLINTNEXTLINE
        CHECK(dict.as_string_dict() ==
            std::unordered_map<Utf8String, Utf8String>());

        REQUIRE(!generator.iterate());
    }
}
