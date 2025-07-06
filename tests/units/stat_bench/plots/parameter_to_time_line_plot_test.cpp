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
 * \brief Test of ParameterToTimeLinePlot class.
 */
#include "stat_bench/plots/parameter_to_time_line_plot.h"

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
#include "stat_bench/measurer/measurement_type.h"
#include "stat_bench/param/num_threads_parameter_name.h"
#include "stat_bench/param/parameter_dict.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value.h"
#include "stat_bench/plot_options.h"
#include "stat_bench/util/ordered_map.h"

TEST_CASE("stat_bench::plots::ParameterToTimeLinePlot") {
    using stat_bench::BenchmarkCaseName;
    using stat_bench::BenchmarkCondition;
    using stat_bench::BenchmarkFullName;
    using stat_bench::BenchmarkGroupName;
    using stat_bench::PlotOptions;
    using stat_bench::clock::Duration;
    using stat_bench::measurer::Measurement;
    using stat_bench::measurer::MeasurementType;
    using stat_bench::param::num_threads_parameter_name;
    using stat_bench::param::ParameterDict;
    using stat_bench::param::ParameterName;
    using stat_bench::param::ParameterValue;
    using stat_bench::plots::ParameterToTimeLinePlot;

    SECTION("write") {
        const auto target_parameter_name = ParameterName("Parameter1");
        const auto parameter_name2 = ParameterName("Parameter2");
        const auto group_name = BenchmarkGroupName("Group");
        const auto case_name1 = BenchmarkCaseName("Case1");
        const auto case_name2 = BenchmarkCaseName("Case2");
        const auto measurement_type = MeasurementType("Measurer");
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
                measurement_type, iterations, 3,
                {{Duration(1), Duration(2), Duration(3)}}, {}, {}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value1")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(4), Duration(5), Duration(6)}}, {}, {}),
            // Case 1, param2=value2
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(2), Duration(3), Duration(4)}}, {}, {}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(5), Duration(6), Duration(7)}}, {}, {}),
            // Case 2
            Measurement(BenchmarkFullName(group_name, case_name2),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(1)},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(3), Duration(4), Duration(5)}}, {}, {}),
            Measurement(BenchmarkFullName(group_name, case_name2),
                BenchmarkCondition(ParameterDict(
                    {{target_parameter_name,
                         ParameterValue().emplace<std::size_t>(2)},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(6), Duration(7), Duration(8)}}, {}, {})};

        SECTION("in linear scale") {
            ParameterToTimeLinePlot plot(
                target_parameter_name, PlotOptions().log_parameter(false));

            const auto file_path =
                std::string("./plots/ParameterToTimeLinePlot.html");
            plot.write(measurement_type, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("in log scale") {
            ParameterToTimeLinePlot plot(
                target_parameter_name, PlotOptions().log_parameter(true));

            const auto file_path =
                std::string("./plots/ParameterToTimeLinePlotLog.html");
            plot.write(measurement_type, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("write with two parameters") {
        const auto parameter_name1 = ParameterName("Parameter1");
        const auto parameter_name2 = ParameterName("Parameter2");
        const auto group_name = BenchmarkGroupName("Group");
        const auto case_name1 = BenchmarkCaseName("Case1");
        const auto measurement_type = MeasurementType("Measurer");
        constexpr std::size_t iterations = 1;
        const auto measurements = std::vector<Measurement>{
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{parameter_name1,
                         ParameterValue().emplace<std::size_t>(1)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value1")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(1), Duration(2), Duration(3)}}, {}, {}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{parameter_name1,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value1")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(2), Duration(3), Duration(4)}}, {}, {}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{parameter_name1,
                         ParameterValue().emplace<std::size_t>(1)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(7), Duration(8), Duration(9)}}, {}, {}),
            Measurement(BenchmarkFullName(group_name, case_name1),
                BenchmarkCondition(ParameterDict(
                    {{parameter_name1,
                         ParameterValue().emplace<std::size_t>(2)},
                        {parameter_name2,
                            ParameterValue().emplace<std::string>("value2")},
                        {num_threads_parameter_name(),
                            ParameterValue().emplace<std::size_t>(1)}})),
                measurement_type, iterations, 3,
                {{Duration(8), Duration(9), Duration(10)}}, {}, {})};

        SECTION("using columns") {
            ParameterToTimeLinePlot plot(parameter_name1,
                PlotOptions().subplot_column_parameter_name(
                    parameter_name2.str().str()));

            const auto file_path =
                std::string("./plots/ParameterToTimeLinePlotColumns.html");
            plot.write(measurement_type, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("using rows") {
            ParameterToTimeLinePlot plot(parameter_name1,
                PlotOptions().subplot_row_parameter_name(
                    parameter_name2.str().str()));

            const auto file_path =
                std::string("./plots/ParameterToTimeLinePlotRows.html");
            plot.write(measurement_type, group_name, measurements, file_path);

            ApprovalTests::Approvals::verify(
                stat_bench_test::read_file(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }
}
