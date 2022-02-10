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
 * \brief Benchmark of a throwing function.
 */
#include <cstdint>
#include <stdexcept>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/util/do_not_optimize.h"

[[nodiscard]] auto throw_exception(std::uint64_t number) -> std::uint64_t {
    throw std::runtime_error("Test exception.");
}

STAT_BENCH_CASE("Error", "throwing function") {
    std::uint64_t number = 30;  // NOLINT
    STAT_BENCH_MEASURE() {
        stat_bench::util::do_not_optimize(number);
        stat_bench::util::do_not_optimize(throw_exception(number));
    };
}

STAT_BENCH_MAIN
