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
 * \brief Test of Measurement class.
 */
#include "stat_bench/measurer/measurement.h"

#include <catch2/catch_test_macros.hpp>

#include "../param/create_ordinary_parameter_dict.h"

TEST_CASE("stat_bench::measurer::Measurement") {
    using stat_bench::clock::Duration;

    SECTION("construct") {
        const auto info = stat_bench::BenchmarkFullName("group", "case");
        const auto cond = stat_bench::BenchmarkCondition(
            2, stat_bench_test::param::create_ordinary_parameter_dict());
        const auto measurer_name = std::string("measurer");
        const std::size_t iterations = 7;
        const std::size_t samples = 2;
        const auto durations = std::vector<std::vector<Duration>>{
            std::vector<Duration>{Duration(1.0), Duration(2.0)},
            std::vector<Duration>{Duration(3.0), Duration(4.0)}};

        std::vector<std::shared_ptr<stat_bench::stat::CustomStatOutput>>
            custom_stat_outputs;
        const auto custom_stat_output1 =
            std::make_shared<stat_bench::stat::CustomStatOutput>(
                "CustomStatOutput1", 2, 3, 2, 1,
                stat_bench::stat::CustomOutputAnalysisType::mean);
        custom_stat_output1->add(0, 0, 1.0);
        custom_stat_output1->add(0, 1, 1.0);
        custom_stat_output1->add(0, 2, 1.0);
        custom_stat_output1->add(1, 0, 1.0);
        custom_stat_output1->add(1, 1, 1.0);
        custom_stat_output1->add(1, 2, 1.0);
        custom_stat_outputs.push_back(custom_stat_output1);

        const std::vector<std::pair<std::string, double>> custom_outputs{
            {"CustomOutput2", 2.0}};

        const auto measurement = stat_bench::measurer::Measurement(info, cond,
            measurer_name, iterations, samples, durations, custom_stat_outputs,
            custom_outputs);

        REQUIRE(measurement.case_info().group_name() == info.group_name());
        REQUIRE(measurement.case_info().case_name() == info.case_name());
        REQUIRE(measurement.cond().threads() == cond.threads());
        REQUIRE(measurement.measurer_name() == measurer_name);
        REQUIRE(measurement.iterations() == iterations);
        REQUIRE(measurement.samples() == samples);

        REQUIRE(measurement.durations().size() == 2);
        REQUIRE(measurement.durations().at(0).size() == 2);
        REQUIRE(measurement.durations().at(0).at(0).seconds() == 1.0);
        REQUIRE(measurement.durations().at(0).at(1).seconds() == 2.0);
        REQUIRE(measurement.durations().at(1).size() == 2);
        REQUIRE(measurement.durations().at(1).at(0).seconds() == 3.0);
        REQUIRE(measurement.durations().at(1).at(1).seconds() == 4.0);
        REQUIRE(measurement.durations_stat().sorted_samples().size() == 4);

        REQUIRE(measurement.custom_stat_outputs().size() == 1);
        REQUIRE(measurement.custom_stat_outputs().at(0)->name() ==
            "CustomStatOutput1");
        REQUIRE(measurement.custom_stat().size() == 1);
        REQUIRE(measurement.custom_stat().at(0).mean() == 1.0);  // NOLINT
        REQUIRE(measurement.custom_outputs().size() == 1);
        REQUIRE(measurement.custom_outputs().at(0).first == "CustomOutput2");
        REQUIRE(measurement.custom_outputs().at(0).second == 2.0);  // NOLINT
    }
}
