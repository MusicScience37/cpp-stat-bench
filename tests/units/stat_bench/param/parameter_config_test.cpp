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
 * \brief Test of ParameterConfig class.
 */
#include "stat_bench/param/parameter_config.h"

#include <string>

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_name.h"

TEST_CASE("stat_bench::param::ParameterConfig") {
    using stat_bench::param::ParameterName;

    SECTION("add parameters") {
        stat_bench::param::ParameterConfig config;

        constexpr int val11 = 3;
        constexpr int val12 = 5;
        config.add<int>(ParameterName("param1"))->add(val11)->add(val12);

        const auto param2 = std::make_shared<
            stat_bench::param::ParameterValueVector<std::string>>();
        const auto val21 = std::string("1");
        const auto val22 = std::string("2");
        const auto val23 = std::string("3");
        config.add<std::string>(ParameterName("param2"))
            ->add(val21)
            ->add(val22)
            ->add(val23);

        auto generator = config.create_generator();

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

    SECTION("check parameter existence") {
        stat_bench::param::ParameterConfig config;

        (void)config.add<int>(ParameterName("param1"));

        REQUIRE(config.has(ParameterName("param1")));
        REQUIRE(!config.has(ParameterName("invalid")));
    }
}
