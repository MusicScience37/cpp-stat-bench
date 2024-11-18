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
 * \brief Test of helper of JSON data files.
 */
#include "stat_bench/reporter/json_data_file_helper.h"

#include <string>
#include <unordered_map>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include "stat_bench/util/utf8_string.h"

TEST_CASE("NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE definitions") {
    using stat_bench::reporter::data_file_spec::CustomOutputData;
    using stat_bench::reporter::data_file_spec::CustomStatOutputData;
    using stat_bench::reporter::data_file_spec::DurationData;
    using stat_bench::reporter::data_file_spec::MeasurementData;
    using stat_bench::reporter::data_file_spec::RootData;
    using stat_bench::reporter::data_file_spec::StatData;
    using stat_bench::util::Utf8String;

    SECTION("serialize and deserialize") {
        RootData data;
        data.started_at = Utf8String("2021-12-28T21:27:01");
        data.finished_at = Utf8String("2021-12-28T21:27:07");

        MeasurementData measurement{};
        measurement.group_name = Utf8String("Group");
        measurement.case_name = Utf8String("Case");
        measurement.params[Utf8String("Param")] = Utf8String("Value");
        measurement.measurer_name = Utf8String("Measurer");
        measurement.iterations = 123;  // NOLINT
        measurement.samples = 12345;   // NOLINT

        measurement.durations.stat.mean = 1.234F;                 // NOLINT
        measurement.durations.stat.max = 2.345F;                  // NOLINT
        measurement.durations.stat.min = 0.123F;                  // NOLINT
        measurement.durations.stat.variance = 3.456F;             // NOLINT
        measurement.durations.stat.standard_deviation = 0.0123F;  // NOLINT
        measurement.durations.values = std::vector<std::vector<float>>{
            {1.0F, 2.0F, 3.0F}, {4.0F, 5.0F, 6.0F}};  // NOLINT

        CustomStatOutputData stat_output{};
        stat_output.name = Utf8String("Stat");
        stat_output.stat.mean = 1.234F;                 // NOLINT
        stat_output.stat.max = 2.345F;                  // NOLINT
        stat_output.stat.min = 0.123F;                  // NOLINT
        stat_output.stat.variance = 3.456F;             // NOLINT
        stat_output.stat.standard_deviation = 0.0123F;  // NOLINT
        stat_output.values = std::vector<std::vector<float>>{
            {1.0F, 2.0F, 3.0F}, {4.0F, 5.0F, 6.0F}};  // NOLINT
        measurement.custom_stat_outputs.push_back(stat_output);

        measurement.custom_outputs.push_back(
            CustomOutputData{Utf8String("Custom"), 3.14F});  // NOLINT

        data.measurements.push_back(measurement);

        const std::string serialized = nlohmann::json(data).dump();
        const auto deserialized =
            nlohmann::json::parse(serialized).get<RootData>();

        REQUIRE(deserialized.started_at == data.started_at);
        REQUIRE(deserialized.finished_at == data.finished_at);
        REQUIRE(deserialized.measurements.size() == data.measurements.size());

        const auto& deserialized_measurement = deserialized.measurements.at(0);
        REQUIRE(deserialized_measurement.group_name == measurement.group_name);
        REQUIRE(deserialized_measurement.case_name == measurement.case_name);
        REQUIRE(deserialized_measurement.params == measurement.params);
        REQUIRE(deserialized_measurement.measurer_name ==
            measurement.measurer_name);
        REQUIRE(deserialized_measurement.iterations == measurement.iterations);
        REQUIRE(deserialized_measurement.samples == measurement.samples);

        REQUIRE(deserialized_measurement.durations.stat.mean ==
            measurement.durations.stat.mean);
        REQUIRE(deserialized_measurement.durations.stat.max ==
            measurement.durations.stat.max);
        REQUIRE(deserialized_measurement.durations.stat.min ==
            measurement.durations.stat.min);
        REQUIRE(deserialized_measurement.durations.stat.variance ==
            measurement.durations.stat.variance);
        REQUIRE(deserialized_measurement.durations.stat.standard_deviation ==
            measurement.durations.stat.standard_deviation);
        REQUIRE(deserialized_measurement.durations.values ==
            measurement.durations.values);

        REQUIRE(deserialized_measurement.custom_stat_outputs.size() ==
            measurement.custom_stat_outputs.size());
        const auto& deserialized_stat_output =
            deserialized_measurement.custom_stat_outputs.at(0);
        REQUIRE(deserialized_stat_output.name == stat_output.name);
        REQUIRE(deserialized_stat_output.stat.mean == stat_output.stat.mean);
        REQUIRE(deserialized_stat_output.stat.max == stat_output.stat.max);
        REQUIRE(deserialized_stat_output.stat.min == stat_output.stat.min);
        REQUIRE(deserialized_stat_output.stat.variance ==
            stat_output.stat.variance);
        REQUIRE(deserialized_stat_output.stat.standard_deviation ==
            stat_output.stat.standard_deviation);
        REQUIRE(deserialized_stat_output.values == stat_output.values);

        REQUIRE(deserialized_measurement.custom_outputs.size() ==
            measurement.custom_outputs.size());
        REQUIRE(deserialized_measurement.custom_outputs.at(0).name ==
            measurement.custom_outputs.at(0).name);
        REQUIRE(deserialized_measurement.custom_outputs.at(0).value ==
            measurement.custom_outputs.at(0).value);
    }
}
