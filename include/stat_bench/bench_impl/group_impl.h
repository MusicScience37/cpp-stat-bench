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
 * \brief Definition of STAT_BENCH_IMPL_GROUP_IMPL macro.
 */
#pragma once

#include "stat_bench/bench_impl/benchmark_group_register.h"  // IWYU pragma: keep

/*!
 * \brief Macro to define and configure a group.
 *
 * \param[in] GROUP_NAME Group name.
 * \param[in] REGISTER_NAME BenchmarkGroupRegister variable name.
 */
#define STAT_BENCH_IMPL_GROUP_IMPL(GROUP_NAME, REGISTER_NAME) \
    static const auto REGISTER_NAME =                         \
        ::stat_bench::bench_impl::BenchmarkGroupRegister(     \
            ::stat_bench::BenchmarkGroupName(GROUP_NAME))
