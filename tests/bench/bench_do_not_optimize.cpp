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
 * \brief Benchmark of do_not_optimize function.
 */
#include <stat_bench/benchmark_macros.h>
#include <stat_bench/do_not_optimize.h>

STAT_BENCH_CASE("do_not_optimize", "do_not_optimize") {
    STAT_BENCH_MEASURE_INDEXED(
        /*thread_index*/, /*sample_index*/, iteration_index) {
        stat_bench::do_not_optimize(iteration_index);
    };
}

STAT_BENCH_CASE("do_not_optimize", "empty") {
    STAT_BENCH_MEASURE_INDEXED(
        /*thread_index*/, /*sample_index*/, iteration_index) {
        (void)iteration_index;
    };
}

STAT_BENCH_MAIN
