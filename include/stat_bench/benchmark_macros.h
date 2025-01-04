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
 * \brief Definition of macros for benchmarks.
 */
#pragma once

#include "stat_bench/bench_impl/benchmark_case_register.h"  // IWYU pragma: export
#include "stat_bench/bench_impl/case_impl.h"
#include "stat_bench/bench_impl/default_main.h"
#include "stat_bench/bench_impl/group_impl.h"
#include "stat_bench/bench_impl/measure_impl.h"
#include "stat_bench/bench_impl/unique_name.h"
#include "stat_bench/fixture_base.h"  // IWYU pragma: keep

/*!
 * \brief Macro to define and configure a group.
 *
 * \param[in] GROUP_NAME Group name.
 *
 * This macro returns stat_bench::bench_impl::BenchmarkGroupRegister object.
 * You can use this macro to configure a group like following:
 *
 * \code {.cpp}
 * STAT_BENCH_GROUP("group_name")
 *     .add_parameter_to_time_plot("parameter_name")
 *     .add_parameter_to_time_plot_log("another_parameter_name");
 * \endcode
 */
#define STAT_BENCH_GROUP(GROUP_NAME) \
    STAT_BENCH_IMPL_GROUP_IMPL(      \
        GROUP_NAME, STAT_BENCH_IMPL_UNIQUE_NAME(stat_bench_group_register_))

/*!
 * \brief Macro to define a case.
 *
 * \param[in] GROUP_NAME Group name.
 * \param[in] CASE_NAME Case name.
 */
#define STAT_BENCH_CASE(GROUP_NAME, CASE_NAME)                              \
    STAT_BENCH_IMPL_CASE_IMPL(STAT_BENCH_IMPL_UNIQUE_NAME(StatBenchCase),   \
        STAT_BENCH_IMPL_UNIQUE_NAME(stat_bench_case_register_), GROUP_NAME, \
        CASE_NAME)

/*!
 * \brief Macro to define a case using a fixture.
 *
 * \param[in] FIXTURE_NAME Fixture name.
 * \param[in] GROUP_NAME Group name.
 * \param[in] CASE_NAME Case name.
 */
#define STAT_BENCH_CASE_F(FIXTURE_NAME, GROUP_NAME, CASE_NAME)                \
    STAT_BENCH_IMPL_CASE_WITH_FIXTURE_IMPL(                                   \
        STAT_BENCH_IMPL_UNIQUE_NAME(StatBenchCase),                           \
        STAT_BENCH_IMPL_UNIQUE_NAME(stat_bench_case_register_), FIXTURE_NAME, \
        GROUP_NAME, CASE_NAME)

/*!
 * \brief Macro to measure a function.
 *
 * \param[in] THREAD_INDEX_VAR Variable name of the index of the thread.
 * \param[in] SAMPLE_INDEX_VAR Variable name of the index of the sample.
 * \param[in] ITERATION_INDEX_VAR Variable name of the index of the iteration.
 */
#define STAT_BENCH_MEASURE_INDEXED(                          \
    THREAD_INDEX_VAR, SAMPLE_INDEX_VAR, ITERATION_INDEX_VAR) \
    STAT_BENCH_IMPL_MEASURE_IMPL(                            \
        THREAD_INDEX_VAR, SAMPLE_INDEX_VAR, ITERATION_INDEX_VAR)

/*!
 * \brief Macro to measure a function.
 */
#define STAT_BENCH_MEASURE()    \
    STAT_BENCH_MEASURE_INDEXED( \
        /*THREAD_INDEX_VAR*/, /*SAMPLE_INDEX_VAR*/, /*ITERATION_INDEX_VAR*/)

/*!
 * \brief Macro of default main function.
 */
#define STAT_BENCH_MAIN STAT_BENCH_IMPL_DEFAULT_MAIN
