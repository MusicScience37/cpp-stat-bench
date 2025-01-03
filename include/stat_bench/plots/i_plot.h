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
 * \brief Definition of IPlot class.
 */
#pragma once

#include <string>
#include <vector>

#include "stat_bench/benchmark_group_name.h"
#include "stat_bench/measurer/measurement.h"
#include "stat_bench/measurer/measurer_name.h"
#include "stat_bench/plots/i_plotter.h"
#include "stat_bench/util/utf8_string.h"

namespace stat_bench {
namespace plots {

/*!
 * \brief Class of interface of plots.
 */
class IPlot {
public:
    /*!
     * \brief Get a name for output files.
     *
     * \return Name.
     */
    [[nodiscard]] virtual auto name_for_file() const
        -> const util::Utf8String& = 0;

    /*!
     * \brief Write a plot.
     *
     * \param[in] plotter Plotter.]
     * \param[in] measurer_name Measurer name.
     * \param[in] group_name Group name.
     * \param[in] measurements Measurements.
     * \param[in] file_path File path of the output.
     */
    virtual void write(IPlotter* plotter,
        const measurer::MeasurerName& measurer_name,
        const BenchmarkGroupName& group_name,
        const std::vector<measurer::Measurement>& measurements,
        const std::string& file_path) = 0;

    /*!
     * \brief Constructor.
     */
    IPlot() = default;

    IPlot(const IPlot&) = delete;
    IPlot(IPlot&&) = delete;
    auto operator=(const IPlot&) -> IPlot& = delete;
    auto operator=(IPlot&&) -> IPlot& = delete;

    /*!
     * \brief Destructor.
     */
    virtual ~IPlot() = default;
};

}  // namespace plots
}  // namespace stat_bench
