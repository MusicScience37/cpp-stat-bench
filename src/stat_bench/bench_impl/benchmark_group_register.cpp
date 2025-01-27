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
#include "stat_bench/custom_output_name.h"
#include "stat_bench/param/parameter_name.h"
#include "stat_bench/plots/parameter_to_output_line_plot.h"
#include "stat_bench/plots/parameter_to_time_box_plot.h"
#include "stat_bench/plots/parameter_to_time_line_plot.h"
#include "stat_bench/plots/parameter_to_time_violin_plot.h"
#include "stat_bench/plots/time_to_output_by_parameter_line_plot.h"
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

auto BenchmarkGroupRegister::add_parameter_to_time_line_plot(
    util::StringView parameter_name, PlotOption::Value options) noexcept
    -> BenchmarkGroupRegister& {
    try {
        const bool plot_parameter_as_log_scale =
            (options & PlotOption::log_parameter) != 0U;
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

auto BenchmarkGroupRegister::add_parameter_to_time_line_plot_log(
    util::StringView parameter_name) noexcept -> BenchmarkGroupRegister& {
    return add_parameter_to_time_line_plot(
        parameter_name, PlotOption::log_parameter);
}

auto BenchmarkGroupRegister::add_parameter_to_time_violin_plot(
    util::StringView parameter_name) noexcept -> BenchmarkGroupRegister& {
    try {
        group_->config().add_plot(
            std::make_shared<plots::ParameterToTimeViolinPlot>(
                param::ParameterName(std::string(
                    parameter_name.data(), parameter_name.size()))));
        return *this;
    } catch (const std::exception& e) {
        std::cerr << "Failed to append a plot to a benchmark group: "
                  << e.what() << std::endl;  // NOLINT(performance-avoid-endl)
        std::exit(1);                        // NOLINT(concurrency-mt-unsafe)
    }
}

auto BenchmarkGroupRegister::add_parameter_to_time_box_plot(
    util::StringView parameter_name) noexcept -> BenchmarkGroupRegister& {
    try {
        group_->config().add_plot(
            std::make_shared<plots::ParameterToTimeBoxPlot>(
                param::ParameterName(std::string(
                    parameter_name.data(), parameter_name.size()))));
        return *this;
    } catch (const std::exception& e) {
        std::cerr << "Failed to append a plot to a benchmark group: "
                  << e.what() << std::endl;  // NOLINT(performance-avoid-endl)
        std::exit(1);                        // NOLINT(concurrency-mt-unsafe)
    }
}

auto BenchmarkGroupRegister::add_parameter_to_output_line_plot(
    util::StringView parameter_name, util::StringView custom_output_name,
    PlotOption::Value options) noexcept -> BenchmarkGroupRegister& {
    try {
        const bool plot_parameter_as_log_scale =
            (options & PlotOption::log_parameter) != 0U;
        const bool plot_custom_output_as_log_scale =
            (options & PlotOption::log_output) != 0U;
        group_->config().add_plot(
            std::make_shared<plots::ParameterToOutputLinePlot>(
                param::ParameterName(
                    std::string(parameter_name.data(), parameter_name.size())),
                CustomOutputName(std::string(
                    custom_output_name.data(), custom_output_name.size())),
                plot_parameter_as_log_scale, plot_custom_output_as_log_scale));
        return *this;
    } catch (const std::exception& e) {
        std::cerr << "Failed to append a plot to a benchmark group: "
                  << e.what() << std::endl;  // NOLINT(performance-avoid-endl)
        std::exit(1);                        // NOLINT(concurrency-mt-unsafe)
    }
}

auto BenchmarkGroupRegister::add_time_to_output_by_parameter_line_plot(
    util::StringView parameter_name, util::StringView custom_output_name,
    PlotOption::Value options) noexcept -> BenchmarkGroupRegister& {
    try {
        const bool plot_custom_output_as_log_scale =
            (options & PlotOption::log_output) != 0U;
        group_->config().add_plot(
            std::make_shared<plots::TimeToOutputByParameterLinePlot>(
                param::ParameterName(
                    std::string(parameter_name.data(), parameter_name.size())),
                CustomOutputName(std::string(
                    custom_output_name.data(), custom_output_name.size())),
                plot_custom_output_as_log_scale));
        return *this;
    } catch (const std::exception& e) {
        std::cerr << "Failed to append a plot to a benchmark group: "
                  << e.what() << std::endl;  // NOLINT(performance-avoid-endl)
        std::exit(1);                        // NOLINT(concurrency-mt-unsafe)
    }
}

}  // namespace bench_impl
}  // namespace stat_bench
