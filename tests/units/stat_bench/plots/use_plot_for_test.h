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
 * \brief Definition of use_plot_for_test function.
 */
#pragma once

#include "../reporter/create_test_measurement.h"
#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/plots/i_plot.h"
#include "stat_bench/plots/i_plotter.h"

namespace stat_bench_test {

inline void use_plot_for_test(stat_bench::plots::IPlot* plot,
    stat_bench::plots::IPlotter* plotter, const std::string& file_path) {
    using stat_bench::BenchmarkGroupName;
    using stat_bench::clock::Duration;
    using stat_bench::measurer::Measurement;
    using stat_bench::measurer::MeasurerName;

    const auto measurer_name = std::string("Measurement1");
    const auto group_name = std::string("Group1");
    const auto measurements = std::vector<Measurement>{
        create_test_measurement(group_name, "Case1", measurer_name,
            std::vector<std::vector<Duration>>{
                std::vector<Duration>{Duration(1.0), Duration(2.0),
                    Duration(2.0), Duration(3.0), Duration(20.0)}}),
        create_test_measurement(group_name, "Case2", measurer_name,
            std::vector<std::vector<Duration>>{std::vector<Duration>{
                Duration(800.0), Duration(900.0), Duration(1000.0)}})};

    plot->write(plotter, MeasurerName(measurer_name),
        BenchmarkGroupName(group_name), measurements, file_path);
}

}  // namespace stat_bench_test
