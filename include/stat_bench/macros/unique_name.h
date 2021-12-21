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
 * \brief Definition of STAT_BENCH_IMPL_UNIQUE_NAME macro.
 */
#pragma once

/*!
 * \brief Macro to get a counter.
 */
#define STAT_BENCH_IMPL_COUNTER __COUNTER__

/*!
 * \brief Macro to concatenate the prefix and the counter.
 *
 * \param[in] PREFIX Prefix.
 * \param[in] COUNTER Counter.
 */
#define STAT_BENCH_IMPL_UNIQUE_NAME_IMPL2(PREFIX, COUNTER) PREFIX##COUNTER

/*!
 * \brief Macro to concatenate the prefix and the counter.
 *
 * \param[in] PREFIX Prefix.
 * \param[in] COUNTER Counter.
 */
#define STAT_BENCH_IMPL_UNIQUE_NAME_IMPL(PREFIX, COUNTER) \
    STAT_BENCH_IMPL_UNIQUE_NAME_IMPL2(PREFIX, COUNTER)

/*!
 * \brief Macro to generate a unique name.
 *
 * \param[in] PREFIX Prefix.
 */
#define STAT_BENCH_IMPL_UNIQUE_NAME(PREFIX) \
    STAT_BENCH_IMPL_UNIQUE_NAME_IMPL(PREFIX, STAT_BENCH_IMPL_COUNTER)
