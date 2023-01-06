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
// IWYU pragma: no_include  <stddef.h>
#include <cstddef>
#include <deque>
#include <exception>
#include <list>
#include <vector>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/current_invocation_context.h"
#include "stat_bench/do_not_optimize.h"
#include "stat_bench/invocation_context.h"

class Fixture : public stat_bench::FixtureBase {
public:
    Fixture() = default;

    template <typename Container>
    void bench(Container& cont_vec) {
        STAT_BENCH_MEASURE_INDEXED(
            /*thread_index*/, sample_index, /*iteration_index*/) {
            cont_vec[sample_index].push_back(0);
        };
        stat_bench::do_not_optimize(cont_vec);
    }
};

STAT_BENCH_CASE_F(Fixture, "push_back", "vector") {
    const std::size_t iterations =
        stat_bench::current_invocation_context().iterations();
    const std::size_t samples =
        stat_bench::current_invocation_context().samples();
    std::vector<std::vector<int>> cont_vec;
    cont_vec.resize(samples);
    bench(cont_vec);
}

STAT_BENCH_CASE_F(Fixture, "push_back", "vector_reserved") {
    const std::size_t iterations =
        stat_bench::current_invocation_context().iterations();
    const std::size_t samples =
        stat_bench::current_invocation_context().samples();
    std::vector<std::vector<int>> cont_vec;
    cont_vec.resize(samples);
    for (std::size_t i = 0; i < samples; ++i) {
        cont_vec.at(i).reserve(iterations);
    }
    bench(cont_vec);
}

STAT_BENCH_CASE_F(Fixture, "push_back", "deque") {
    const std::size_t iterations =
        stat_bench::current_invocation_context().iterations();
    const std::size_t samples =
        stat_bench::current_invocation_context().samples();
    std::vector<std::deque<int>> cont_vec;
    cont_vec.resize(samples);
    bench(cont_vec);
}

STAT_BENCH_CASE_F(Fixture, "push_back", "list") {
    const std::size_t iterations =
        stat_bench::current_invocation_context().iterations();
    const std::size_t samples =
        stat_bench::current_invocation_context().samples();
    std::vector<std::list<int>> cont_vec;
    cont_vec.resize(samples);
    bench(cont_vec);
}

STAT_BENCH_MAIN
