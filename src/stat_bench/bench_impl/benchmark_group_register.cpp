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
 * \brief Implementation of BenchmarkGroup class.
 */
#include "stat_bench/bench_impl/benchmark_group_register.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include "stat_bench/bench_impl/benchmark_case_registry.h"
#include "stat_bench/bench_impl/benchmark_group_config.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/plots/parameter_to_time_line_plot.h"
#include "stat_bench/util/string_view.h"

namespace stat_bench {
namespace bench_impl {

BenchmarkGroupRegister::BenchmarkGroupRegister(
    const BenchmarkGroupName& name) noexcept {
    try {
        group_ = &BenchmarkCaseRegistry::instance().add_or_get_group(name);
    } catch (const std::exception& e) {
        std::cerr << "Failed to append a benchmark group: " << e.what()
                  << std::endl;  // NOLINT(performance-avoid-endl)
        std::exit(1);            // NOLINT(concurrency-mt-unsafe)
    }
}

auto BenchmarkGroupRegister::add_parameter_to_time_plot(
    util::StringView parameter_name) noexcept -> BenchmarkGroupRegister& {
    try {
        constexpr bool plot_parameter_as_log_scale = false;
        group_->config().add_plot(
            std::make_shared<plots::ParameterToTimeLinePlot>(
                param::ParameterName(
                    std::string(parameter_name.data(), parameter_name.size())),
                plot_parameter_as_log_scale));
        return *this;
    } catch (const std::exception& e) {
        std::cerr << "Failed to append a plot to a benchmark group: "
                  << e.what() << std::endl;  // NOLINT(performance-avoid-endl)
        std::exit(1);                        // NOLINT(concurrency-mt-unsafe)
    }
}

auto BenchmarkGroupRegister::add_parameter_to_time_plot_log(
    util::StringView parameter_name) noexcept -> BenchmarkGroupRegister& {
    try {
        constexpr bool plot_parameter_as_log_scale = true;
        group_->config().add_plot(
            std::make_shared<plots::ParameterToTimeLinePlot>(
                param::ParameterName(
                    std::string(parameter_name.data(), parameter_name.size())),
                plot_parameter_as_log_scale));
        return *this;
    } catch (const std::exception& e) {
        std::cerr << "Failed to append a plot to a benchmark group: "
                  << e.what() << std::endl;  // NOLINT(performance-avoid-endl)
        std::exit(1);                        // NOLINT(concurrency-mt-unsafe)
    }
}

}  // namespace bench_impl
}  // namespace stat_bench
