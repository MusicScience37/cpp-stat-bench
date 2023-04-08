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
 * \brief Definition of BenchmarkCaseRegister class.
 */
#pragma once

#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>

#include "stat_bench/bench_impl/benchmark_case_registry.h"

namespace stat_bench {
namespace bench_impl {

/*!
 * \brief Class to register benchmarks.
 *
 * \tparam Benchmark Type of benchmark.
 */
template <typename Benchmark>
class BenchmarkCaseRegister {
public:
    /*!
     * \brief Constructor.
     */
    BenchmarkCaseRegister() noexcept {
        try {
            BenchmarkCaseRegistry::instance().add(
                std::make_shared<Benchmark>());
        } catch (const std::exception& e) {
            std::cerr << "Failed to append a benchmark: " << e.what()
                      << std::endl;
            std::exit(1);  // NOLINT(concurrency-mt-unsafe)
        }
    }
};

}  // namespace bench_impl
}  // namespace stat_bench
