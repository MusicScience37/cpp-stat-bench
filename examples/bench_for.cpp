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
 * \brief Benchmark of push_back in STL containers.
 */
#include <cstddef>
#include <vector>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/do_not_optimize.h"

constexpr std::size_t size = 100000;

STAT_BENCH_CASE("for", "indexed access") {
    auto vec = std::vector<int>(size, 0);
    STAT_BENCH_MEASURE() {
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (std::size_t i = 0; i < vec.size(); ++i) {
            ++vec[i];
        }
        stat_bench::do_not_optimize(vec);
    };
}

STAT_BENCH_CASE("for", "indexed access (cached size)") {
    auto vec = std::vector<int>(size, 0);
    STAT_BENCH_MEASURE() {
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (std::size_t i = 0, vec_size = vec.size(); i < vec_size; ++i) {
            ++vec[i];
        }
        stat_bench::do_not_optimize(vec);
    };
}

STAT_BENCH_CASE("for", "iterator") {
    auto vec = std::vector<int>(size, 0);
    STAT_BENCH_MEASURE() {
        // NOLINTNEXTLINE(modernize-loop-convert)
        for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
            ++(*iter);
        }
        stat_bench::do_not_optimize(vec);
    };
}

STAT_BENCH_CASE("for", "range for") {
    auto vec = std::vector<int>(size, 0);
    STAT_BENCH_MEASURE() {
        for (int& val : vec) {
            ++val;
        }
        stat_bench::do_not_optimize(vec);
    };
}

STAT_BENCH_MAIN
