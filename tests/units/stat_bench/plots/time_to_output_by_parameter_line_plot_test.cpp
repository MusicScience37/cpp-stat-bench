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
 * \brief Test of TimeToOutputByParameterLinePlot class.
 */
#include "stat_bench/plots/time_to_output_by_parameter_line_plot.h"

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../reporter/read_file.h"
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_condition.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/custom_output_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/num_threads_parameter_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/stat/custom_stat_output.h"
#include "stat_bench/util/ordered_map.h"

TEST_CASE("stat_bench::plots::TimeToOutputByParameterLinePlot") {
    using stat_bench::BenchmarkCaseName;
    using stat_bench::BenchmarkCondition;
    using stat_bench::BenchmarkFullName;
    using stat_bench::BenchmarkGroupName;
    using stat_bench::CustomOutputName;
    using stat_bench::clock::Duration;
    using stat_bench::measurer::Measurement;
    using stat_bench::measurer::MeasurerName;
    using stat_bench::param::num_threads_parameter_name;
    using stat_bench::param::ParameterDict;
    using stat_bench::param::ParameterName;
    using stat_bench::param::ParameterValue;
    using stat_bench::plots::TimeToOutputByParameterLinePlot;

    SECTION("write without statistics") {
        const auto target_parameter_name = ParameterName("Parameter1");
        const auto parameter_name2 = ParameterName("Parameter2");
        const auto target_output_name = CustomOutputName("Output1");
        const auto output_name2 = CustomOutputName("Output2");
        const auto group_name = BenchmarkGroupName("Group");
        const auto case_name1 = BenchmarkCaseName("Case1");
        const auto case_name2 = BenchmarkCaseName("Case2");
        const auto measurer_name = MeasurerName("Measurer");
        constexpr std::size_t iterations = 1;
        const auto measurements = std::vector<Measurement>{
            // Case 1, param2=value1
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value1")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(1), Duration(2), Duration(3)}}, {},
                {{target_output_name, 1.1}, {output_name2, -1.0}}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value1")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(4), Duration(5), Duration(6)}}, {},
                {{target_output_name, 2.2}, {output_name2, -1.0}}),
            // Case 1, param2=value2
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(2), Duration(3), Duration(4)}}, {},
                {{target_output_name, 3.3}, {output_name2, -1.0}}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(5), Duration(6), Duration(7)}}, {},
                {{target_output_name, 4.4}, {output_name2, -1.0}}),
            // Case 2
            Measurement(BenchmarkFullName(group_name, case_name2),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(3), Duration(4), Duration(5)}}, {},
                {{target_output_name, 5.5}, {output_name2, -1.0}}),
            Measurement(BenchmarkFullName(group_name, case_name2),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(6), Duration(7), Duration(8)}}, {},
                {{target_output_name, 6.6}, {output_name2, -1.0}})};

        SECTION("in linear scale") {
            constexpr bool plot_custom_output_as_log_scale = false;
            TimeToOutputByParameterLinePlot plot(target_parameter_name,
                target_output_name, plot_custom_output_as_log_scale);

            const auto file_path =
                std::string("./plots/TimeToOutputByParameterLinePlot.html");
            plot.write(measurer_name, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in log scale") {
            constexpr bool plot_custom_output_as_log_scale = true;
            TimeToOutputByParameterLinePlot plot(target_parameter_name,
                target_output_name, plot_custom_output_as_log_scale);

            const auto file_path =
                std::string("./plots/TimeToOutputByParameterLinePlotLog.html");
            plot.write(measurer_name, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("write with statistics") {
        const auto target_parameter_name = ParameterName("Parameter1");
        const auto parameter_name2 = ParameterName("Parameter2");
        const auto target_output_name = CustomOutputName("Output1");
        const auto output_name2 = CustomOutputName("Output2");
        const auto group_name = BenchmarkGroupName("Group");
        const auto case_name1 = BenchmarkCaseName("Case1");
        const auto case_name2 = BenchmarkCaseName("Case2");
        const auto measurer_name = MeasurerName("Measurer");
        static constexpr std::size_t threads = 1;
        static constexpr std::size_t iterations = 1;

        const auto create_output = [](const CustomOutputName& name,
                                       double value) {
            auto output = std::make_shared<stat_bench::stat::CustomStatOutput>(
                name, threads, 3, 0, iterations,
                stat_bench::stat::CustomOutputAnalysisType::mean);
            output->add(0, 0, value - 1.0);
            output->add(0, 1, value);
            output->add(0, 2, value + 1.0);
            return output;
        };

        const auto measurements = std::vector<Measurement>{
            // Case 1, param2=value1
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value1")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(1), Duration(2), Duration(3)}},
                {create_output(target_output_name, 1.1),
                    create_output(output_name2, -1.0)},
                {}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value1")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(4), Duration(5), Duration(6)}},
                {create_output(target_output_name, 2.2),
                    create_output(output_name2, -1.0)},
                {}),
            // Case 1, param2=value2
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(2), Duration(3), Duration(4)}},
                {create_output(target_output_name, 3.3),
                    create_output(output_name2, -1.0)},
                {}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(5), Duration(6), Duration(7)}},
                {create_output(target_output_name, 4.4),
                    create_output(output_name2, -1.0)},
                {}),
            // Case 2
            Measurement(BenchmarkFullName(group_name, case_name2),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(3), Duration(4), Duration(5)}},
                {create_output(target_output_name, 5.5),
                    create_output(output_name2, -1.0)},
                {}),
            Measurement(BenchmarkFullName(group_name, case_name2),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurer_name, iterations, 3,
                {{Duration(6), Duration(7), Duration(8)}},
                {create_output(target_output_name, 6.6),
                    create_output(output_name2, -1.0)},
                {})};

        SECTION("in linear scale") {
            constexpr bool plot_custom_output_as_log_scale = false;
            TimeToOutputByParameterLinePlot plot(target_parameter_name,
                target_output_name, plot_custom_output_as_log_scale);

            const auto file_path =
                std::string("./plots/TimeToOutputByParameterLinePlotStat.html");
            plot.write(measurer_name, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in log scale") {
            constexpr bool plot_custom_output_as_log_scale = true;
            TimeToOutputByParameterLinePlot plot(target_parameter_name,
                target_output_name, plot_custom_output_as_log_scale);

            const auto file_path = std::string(
                "./plots/TimeToOutputByParameterLinePlotStatLog.html");
            plot.write(measurer_name, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }
}
