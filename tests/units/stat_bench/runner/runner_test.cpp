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
 * \brief Test of Runner class.
 */
#include "stat_bench/runner/runner.h"

#include <cstddef>
#include <exception>
#include <stdexcept>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>

#include "../measurer/mock_measurer.h"
#include "../mock_benchmark_case.h"
#include "../reporter/mock_reporter.h"
#include "stat_bench/benchmark_case_name.h"
#include "stat_bench/benchmark_full_name.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/clock/duration.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/param/parameter_config.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/param/parameter_value_vector.h"

TEST_CASE("stat_bench::runner::Runner") {
    using stat_bench::BenchmarkCaseName;
    using stat_bench::BenchmarkFullName;
    using stat_bench::BenchmarkGroupName;
    using stat_bench::measurer::MeasurerName;
    using stat_bench::param::ParameterName;

    const auto measurer =
        std::make_shared<stat_bench_test::measurer::MockMeasurer>();

    const auto measurer_name = MeasurerName("measurer");
    ALLOW_CALL(*measurer, name())
        // NOLINTNEXTLINE
        .RETURN(measurer_name);

    const auto reporter =
        std::make_shared<stat_bench_test::reporter::MockReporter>();

    const auto empty_param_config = stat_bench::param::ParameterConfig();

    SECTION("perform a benchmark") {
        const auto group_name1 = BenchmarkGroupName("Group1");
        const auto case_name1 = BenchmarkCaseName("case1");
        const auto info1 = BenchmarkFullName(group_name1, case_name1);
        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();

        ALLOW_CALL(*case1, info())
            // NOLINTNEXTLINE
            .RETURN(info1);
        ALLOW_CALL(*case1, params())
            // NOLINTNEXTLINE
            .RETURN(empty_param_config);

        stat_bench::bench_impl::BenchmarkCaseRegistry registry;
        registry.add(case1);

        stat_bench::runner::Runner runner{registry};

        runner.add(measurer);
        runner.add(reporter);

        trompeloeil::sequence seq;

        REQUIRE_CALL(*reporter, experiment_starts(trompeloeil::_))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, measurer_starts(measurer_name))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, group_starts(group_name1, trompeloeil::_))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, case_starts(trompeloeil::_)).IN_SEQUENCE(seq);

        const std::size_t iterations = 7;
        const std::size_t samples = 11;
        const auto durations =
            std::vector<std::vector<stat_bench::clock::Duration>>{
                std::vector<stat_bench::clock::Duration>{
                    stat_bench::clock::Duration(123.0)}};
        REQUIRE_CALL(*measurer, measure(trompeloeil::_, trompeloeil::_))
            // NOLINTNEXTLINE
            .RETURN(stat_bench::measurer::Measurement(_1->info(), _2,
                measurer_name, iterations, samples, durations, {}, {}))
            .IN_SEQUENCE(seq);

        std::shared_ptr<stat_bench::measurer::Measurement> measurement;
        REQUIRE_CALL(*reporter, measurement_succeeded(trompeloeil::_))
            // NOLINTNEXTLINE
            .LR_SIDE_EFFECT(
                measurement =
                    std::make_shared<stat_bench::measurer::Measurement>(_1))
            .IN_SEQUENCE(seq);
        FORBID_CALL(*reporter,
            measurement_failed(trompeloeil::_, trompeloeil::_, trompeloeil::_));

        REQUIRE_CALL(*reporter, case_finished(trompeloeil::_)).IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, group_finished(group_name1)).IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, measurer_finished(measurer_name))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, experiment_finished(trompeloeil::_))
            .IN_SEQUENCE(seq);

        runner.run();

        REQUIRE(measurement->case_info().group_name() == group_name1);
        REQUIRE(measurement->case_info().case_name() == case_name1);
        REQUIRE(measurement->cond().threads() == 1);
        REQUIRE(measurement->measurer_name() == measurer_name);
        REQUIRE(measurement->iterations() == iterations);
        REQUIRE(measurement->samples() == samples);
        REQUIRE(measurement->durations().size() == 1);
        REQUIRE(measurement->durations().at(0).size() == 1);
        REQUIRE(measurement->durations().at(0).at(0).seconds() == 123.0);
    }

    SECTION("perform a benchmark to fail") {
        const auto group_name1 = BenchmarkGroupName("Group1");
        const auto case_name1 = BenchmarkCaseName("case1");
        const auto info1 = BenchmarkFullName(group_name1, case_name1);
        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();

        ALLOW_CALL(*case1, info())
            // NOLINTNEXTLINE
            .RETURN(info1);
        ALLOW_CALL(*case1, params())
            // NOLINTNEXTLINE
            .RETURN(empty_param_config);

        stat_bench::bench_impl::BenchmarkCaseRegistry registry;
        registry.add(case1);

        stat_bench::runner::Runner runner{registry};

        runner.add(measurer);
        runner.add(reporter);

        trompeloeil::sequence seq;

        REQUIRE_CALL(*reporter, experiment_starts(trompeloeil::_))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, measurer_starts(measurer_name))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, group_starts(group_name1, trompeloeil::_))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, case_starts(trompeloeil::_)).IN_SEQUENCE(seq);

        const auto durations =
            std::vector<std::vector<stat_bench::clock::Duration>>{
                std::vector<stat_bench::clock::Duration>{
                    stat_bench::clock::Duration(123.0)}};
        REQUIRE_CALL(*measurer, measure(trompeloeil::_, trompeloeil::_))
            // NOLINTNEXTLINE
            .THROW(std::runtime_error("Test exception."))
            .IN_SEQUENCE(seq);

        std::exception_ptr error;
        REQUIRE_CALL(*reporter,
            measurement_failed(trompeloeil::_, trompeloeil::_, trompeloeil::_))
            // NOLINTNEXTLINE
            .LR_SIDE_EFFECT(error = _3)
            .IN_SEQUENCE(seq);
        FORBID_CALL(*reporter, measurement_succeeded(trompeloeil::_));

        REQUIRE_CALL(*reporter, case_finished(trompeloeil::_)).IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, group_finished(group_name1)).IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, measurer_finished(measurer_name))
            .IN_SEQUENCE(seq);
        REQUIRE_CALL(*reporter, experiment_finished(trompeloeil::_))
            .IN_SEQUENCE(seq);

        runner.run();

        REQUIRE(error);
        REQUIRE_THROWS_AS(std::rethrow_exception(error), std::runtime_error);
    }

    SECTION("execute parametrized case") {
        const auto group_name1 = BenchmarkGroupName("Group1");
        const auto case_name1 = BenchmarkCaseName("case1");
        const auto info1 = BenchmarkFullName(group_name1, case_name1);
        const auto case1 =
            std::make_shared<stat_bench_test::bench_impl::MockBenchmarkCase>();
        auto param_config = empty_param_config;
        param_config.add<int>(ParameterName("param1"))
            ->add(1)
            ->add(2);  // NOLINT
        param_config.add<int>(ParameterName("param2"))
            ->add(3)
            ->add(4)
            ->add(5);  // NOLINT

        ALLOW_CALL(*case1, info())
            // NOLINTNEXTLINE
            .RETURN(info1);
        ALLOW_CALL(*case1, params())
            // NOLINTNEXTLINE
            .RETURN(param_config);

        stat_bench::bench_impl::BenchmarkCaseRegistry registry;
        registry.add(case1);

        stat_bench::runner::Runner runner{registry};

        runner.add(measurer);

        const std::size_t iterations = 7;
        const std::size_t samples = 11;
        const auto durations =
            std::vector<std::vector<stat_bench::clock::Duration>>{
                std::vector<stat_bench::clock::Duration>{
                    stat_bench::clock::Duration(123.0)}};
        std::vector<stat_bench::BenchmarkCondition> conditions;
        REQUIRE_CALL(*measurer, measure(trompeloeil::_, trompeloeil::_))
            // NOLINTNEXTLINE
            .LR_SIDE_EFFECT(conditions.push_back(_2))
            // NOLINTNEXTLINE
            .RETURN(stat_bench::measurer::Measurement(_1->info(), _2,
                measurer_name, iterations, samples, durations, {}, {}))
            // NOLINTNEXTLINE
            .TIMES(6);

        runner.run();

        REQUIRE(conditions.size() == 6);
    }
}
