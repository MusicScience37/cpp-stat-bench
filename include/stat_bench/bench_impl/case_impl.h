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
 * \brief Definition of STAT_BENCH_IMPL_CASE_IMPL macro.
 */
#pragma once

#include "stat_bench/bench_impl/benchmark_case_helper.h"    // IWYU pragma: keep
#include "stat_bench/bench_impl/benchmark_case_register.h"  // IWYU pragma: keep
#include "stat_bench/bench_impl/null_fixture.h"             // IWYU pragma: keep
#include "stat_bench/benchmark_case_name.h"                 // IWYU pragma: keep
#include "stat_bench/benchmark_group_name.h"                // IWYU pragma: keep

/*!
 * \brief Macro to define a case using a fixture.
 *
 * \param[in] CLASS_NAME Class name.
 * \param[in] REGISTER_NAME BenchmarkCaseRegister variable name.
 * \param[in] FIXTURE_NAME Fixture name.
 * \param[in] GROUP_NAME Group name.
 * \param[in] CASE_NAME Case name.
 */
#define STAT_BENCH_IMPL_CASE_WITH_FIXTURE_IMPL(                              \
    CLASS_NAME, REGISTER_NAME, FIXTURE_NAME, GROUP_NAME, CASE_NAME)          \
                                                                             \
    namespace {                                                              \
                                                                             \
    class CLASS_NAME final                                                   \
        : public ::stat_bench::bench_impl::BenchCaseHelper<FIXTURE_NAME> {   \
    public:                                                                  \
        CLASS_NAME()                                                         \
            : BenchCaseHelper(::stat_bench::BenchmarkGroupName(GROUP_NAME),  \
                  ::stat_bench::BenchmarkCaseName(CASE_NAME)) {}             \
                                                                             \
        void run() override;                                                 \
    };                                                                       \
                                                                             \
    static const ::stat_bench::bench_impl::BenchmarkCaseRegister<CLASS_NAME> \
        REGISTER_NAME;                                                       \
                                                                             \
    } /* namespace */                                                        \
                                                                             \
    void CLASS_NAME::run()

/*!
 * \brief Macro to define a case.
 *
 * \param[in] CLASS_NAME Class name.
 * \param[in] REGISTER_NAME BenchmarkCaseRegister variable name.
 * \param[in] GROUP_NAME Group name.
 * \param[in] CASE_NAME Case name.
 */
#define STAT_BENCH_IMPL_CASE_IMPL(                                    \
    CLASS_NAME, REGISTER_NAME, GROUP_NAME, CASE_NAME)                 \
    STAT_BENCH_IMPL_CASE_WITH_FIXTURE_IMPL(CLASS_NAME, REGISTER_NAME, \
        ::stat_bench::bench_impl::NullFixture, GROUP_NAME, CASE_NAME)
