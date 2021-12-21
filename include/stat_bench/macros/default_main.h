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
 * \brief Definition of STAT_BENCH_IMPL_DEFAULT_MAIN macro.
 */
#pragma once

#include <cstdlib>
#include <iostream>

#include "stat_bench/runner.h"

namespace stat_bench {
namespace impl {

/*!
 * \brief Default main function.
 *
 * \return Exit code.
 */
auto default_main(int /*argc*/, char** /*argv*/) noexcept -> int {
    try {
        stat_bench::Runner runner;
        runner.init();
        runner.run();
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

}  // namespace impl
}  // namespace stat_bench

/*!
 * \brief Macro of default main function.
 */
#define STAT_BENCH_IMPL_DEFAULT_MAIN                         \
    auto main(int argc, char** argv)->int {                  \
        return ::stat_bench::impl::default_main(argc, argv); \
    }
