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
 * \brief Benchmark of STL containers.
 */
#include <cstddef>
#include <deque>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "stat_bench/benchmark_macros.h"
#include "stat_bench/fixture_base.h"
#include "stat_bench/invocation_context.h"
#include "stat_bench/param/parameter_value_vector.h"

class Fixture : public stat_bench::FixtureBase {
public:
    Fixture() {
        // NOLINTNEXTLINE
        add_param<std::size_t>("size")->add(100)->add(1000)->add(10000);
    }

    void setup(stat_bench::InvocationContext& context) override {
        size_ = context.get_param<std::size_t>("size");
    }

protected:
    std::size_t size_{0};
};

STAT_BENCH_MAIN

STAT_BENCH_GROUP("push_back").add_parameter_to_time_plot_log("size");

STAT_BENCH_CASE_F(Fixture, "push_back", "vector") {
    const std::size_t size = size_;
    STAT_BENCH_MEASURE() {
        std::vector<int> vec;
        for (std::size_t i = 0; i < size; ++i) {
            vec.push_back(0);  // NOLINT
        }
    };
}

STAT_BENCH_CASE_F(Fixture, "push_back", "vector_reserved") {
    const std::size_t size = size_;
    STAT_BENCH_MEASURE() {
        std::vector<int> vec;
        vec.reserve(size);
        for (std::size_t i = 0; i < size; ++i) {
            vec.push_back(0);
        }
    };
}

STAT_BENCH_CASE_F(Fixture, "push_back", "deque") {
    const std::size_t size = size_;
    STAT_BENCH_MEASURE() {
        std::deque<int> deq;
        for (std::size_t i = 0; i < size; ++i) {
            deq.push_back(0);
        }
    };
}

STAT_BENCH_CASE_F(Fixture, "push_back", "list") {
    const std::size_t size = size_;
    STAT_BENCH_MEASURE() {
        std::list<int> lst;
        for (std::size_t i = 0; i < size; ++i) {
            lst.push_back(0);
        }
    };
}
