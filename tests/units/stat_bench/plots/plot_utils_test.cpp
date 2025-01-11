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
 * \brief Test of utility functions for plots.
 */
#include "stat_bench/plots/plot_utils.h"

#include <string>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/util/ordered_map.h"

TEST_CASE("stat_bench::plots::generate_plot_name") {
    using stat_bench::BenchmarkCaseName;
    using stat_bench::param::ParameterDict;
    using stat_bench::param::ParameterName;
    using stat_bench::param::ParameterValue;
    using stat_bench::plots::generate_plot_name;

    SECTION("generate a name with an empty parameter dictionary") {
        const BenchmarkCaseName case_name{"case_name"};
        const ParameterDict params{{}};

        const auto name = generate_plot_name(case_name, params);

        CHECK(name.str() == "case_name");
    }

    SECTION("generate a name with one parameter") {
        const BenchmarkCaseName case_name{"case_name"};
        const ParameterDict params{
            {{ParameterName("param1"), ParameterValue().emplace<int>(3)}}};

        const auto name = generate_plot_name(case_name, params);

        CHECK(name.str() == "case_name (param1=3)");
    }

    SECTION("generate a name with two parameters") {
        const BenchmarkCaseName case_name{"case_name"};
        const ParameterDict params{
            {{ParameterName("param1"), ParameterValue().emplace<int>(3)},
                {ParameterName("param2"),
                    ParameterValue().emplace<std::string>("str")}}};

        const auto name = generate_plot_name(case_name, params);

        CHECK(name.str() == "case_name (param1=3, param2=str)");
    }
}
